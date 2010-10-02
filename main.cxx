/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2003 James Bernsen
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; version 2 of the License.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
/////////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdlib.h>

#include <qapplication.h>
#include <qdir.h>
#include <qfileinfo.h>
#include <qstring.h>

#include "const.hxx"
#include "Environment.hxx"

#include "IqHtml.hxx"

#ifdef Q_WS_WIN
#include <conio.h>
#else
#include <curses.h>
#endif




/***************** PROTOTYPES *****************/
void displayHelp(const QString&, const QStringList&);
void displayVersionInfo();


/***************************************************************************/
//! This is the main function.
/***************************************************************************/
int main(int argc, char **argv) {

   Environment::ArgMap argMap;

   try {
      QStringList recognize;

      recognize.push_back("-h*");
      recognize.push_back("-version*");
      recognize.push_back("-debug");
      recognize.push_back("-out:");
      recognize.push_back("-cleanTitle");
      recognize.push_back("-noBlankData");
      recognize.push_back("-listType:");
      recognize.push_back("-noSketches");
      recognize.push_back("-sketchDir:");
      recognize.push_back("-sketchFormat:");
      recognize.push_back("-pause");

      try {
         argMap = Environment::getArgMap(argc, argv, recognize);
      }
      catch (QString &exc) {
         cerr << exc << endl;
         exit(EXIT_FAILURE);
      }

      bool sketchesEnabled = !(argMap.find("-noSketches") != argMap.end());

      QApplication app(argc, argv, sketchesEnabled);

      QStringList validSketchFormats;
      validSketchFormats.push_back("JPEG");
      validSketchFormats.push_back("PNG");

      if (argMap.find("-h") != argMap.end()) {
         displayHelp(argv[0], validSketchFormats);
         return 0;
      }

      if (argMap.find("-version") != argMap.end()) {
         displayVersionInfo();
         return 0;
      }

      bool debug (argMap.find("-debug") != argMap.end());

      QString inFilename;
      if (argc > 1) {
         inFilename = argv[1];
      }
      else {
         displayHelp(argv[0], validSketchFormats);
         cerr << "An input filename must be supplied." << endl;
         return 1;
      }

      QString outFilename;
      if (argMap.find("-out") != argMap.end()) {
         outFilename = argMap["-out"];
      }
      else {
         outFilename = inFilename;
         QString ext("." + QFileInfo(inFilename).extension(true));
         outFilename = outFilename.left( outFilename.length() - ext.length());
         outFilename += ".html";
         qDebug(outFilename);
      }

      QString listType("tabled");
      if (argMap.find("-listType") != argMap.end()) {
         listType = argMap["-listType"];
      }

      QString sketchDir;
      if (argMap.find("-sketchDir") != argMap.end()) {
         sketchDir = argMap["-sketchDir"];
      }
      else {
         sketchDir = "sketches";
      }

      if (sketchesEnabled) {
         QDir dir(sketchDir);
         if (!dir.exists()) {
            dir = QDir::current();
            if (!dir.mkdir(sketchDir)) {
               cerr << QString("Could not create the sketch directory (%1).")
                     .arg(sketchDir) << endl;
            }
         }
      }

      QString sketchFormat("PNG");
      if (argMap.find("-sketchFormat") != argMap.end()) {
         sketchFormat = QString(argMap["-sketchFormat"]).upper();
         if (!validSketchFormats.contains(sketchFormat)) {
            displayHelp(argv[0], validSketchFormats);
            cerr << QString("The specified sketch format (%1) is invalid.  "
                  "Valid sketch formats are: %2.").arg(sketchFormat)
                  .arg(validSketchFormats.join(" ")) << endl;
         }
      }


      Style style;
      style.setNoBlankValues(argMap.find("-noBlankData") != argMap.end());
      style.setCleanTitle(argMap.find("-cleanTitle") != argMap.end());
      style.setListViewType(listType);
      style.setSketchesEnabled(sketchesEnabled);
      style.setSketchDir(sketchDir);
      style.setSketchFormat(sketchFormat);

      IqHtml* iqhtml = new IqHtml();
      iqhtml->setDebug(debug);
      iqhtml->setInFilename(inFilename);
      iqhtml->setOutFilename(outFilename);
      iqhtml->process(style);
      delete iqhtml;

   }
   catch(QString &exc) {
      cerr << "Caught unexpected exception: " << exc << endl;
   }
   catch(...) {
      cerr << "Caught unexpected exception." << endl;
   }

   if (argMap.find("-pause") != argMap.end()) {
      cout << endl << "Press any key to continue..." << endl;
#ifdef Q_WS_WIN
      _getch();
#else
      getch();
#endif
   }

   return 0;
}



/***************************************************************************/
//! Displays help information.
/***************************************************************************/
void displayHelp(const QString& progname, const QStringList& validSketchFormats) {
   cout << endl;
   cout << AppConst::APPLICATION_TITLE << " - convert IQNotes XML to HTML" << endl;
   cout << endl;
   cout << progname << " <infile>" << endl;
   cout << endl;
   cout << " -cleanTitle            Removes the file extension from and converts" << endl;
   cout << "                        underscores to spaces in the input filename." << endl;
   cout << " -listType <type>       Specifies the list type (either \"tabled\" or" << endl;
   cout << "                        \"bulleted\")." << endl;
   cout << "                        The default setting is \"tabled\"." << endl;
   cout << " -noBlankData           Does not print blank note data lines." << endl;
   cout << " -noSketches            Disables sketch creation (allows IqHtml to be run" << endl;
   cout << "                        without a window system)." << endl;
   cout << " -out <outfile>         Specifies the output filename." << endl;
   cout << " -pause                 Forces the application to wait for a keypress before" << endl;
   cout << "                        closing.  (Useful when running iqhtml by dragging XML" << endl;
   cout << "                        files onto its desktop icon.)" << endl;
   cout << " -sketchDir <dir>       Specifies the directory where sketch images should be" << endl;
   cout << "                        placed.  (If the \"-noSketches\" option is used, this" << endl;
   cout << "                        option is ignored.)" << endl;
   cout << " -sketchFormat <fmt>    Specifies the file format for sketch images." << endl;
   cout << QString("                        Valid sketch formats are: %1.").arg(validSketchFormats.join(" ")) << endl;
   cout << "                        (If the \"-noSketches\" option is used, this option" << endl;
   cout << "                        is ignored.)" << endl;
   cout << " -version               Displays the version of this application." << endl;
   cout << endl;
   cout << "For the latest version of " << AppConst::APPLICATION_TITLE << ", go to: " << endl;
   cout << AppConst::APPLICATION_WEBSITE << endl;
   cout << endl;
}



/***************************************************************************/
//! Displays version information.
/***************************************************************************/
void displayVersionInfo() {
   cout << AppConst::MAJOR_VERSION << "." << AppConst::MINOR_VERSION << "." << AppConst::REVISION_NUMBER << endl;
   cout << endl;
}



