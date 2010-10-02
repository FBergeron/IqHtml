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


/***************************************************************************/
/*!
   \file    NoteHtmlWriter.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream.h>

#include <qdatetime.h>
#include <qdir.h>
#include <qglobal.h>
#include <qpainter.h>
#include <qpixmap.h>
#include <qregexp.h>
#include <qstring.h>

#include "const.hxx"
#include "Environment.hxx"
#include "qsketch.h"
#include "NoteHtmlWriter.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
NoteHtmlWriter::NoteHtmlWriter() : _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
NoteHtmlWriter::~NoteHtmlWriter() {
} // end destructor



/***************************************************************************/
//! Generates HTML and sets top-level settings.
/***************************************************************************/
void NoteHtmlWriter::generateHtml(QTextStream& out, const QString& htmlFilePath,
      const Style& style, Note* note, int maxDepth) {

   _htmlFilePath = htmlFilePath;
   _treeColumns = maxDepth;
   _generateHtml(out, style, note, 1);
}



/***************************************************************************/
//! Generates HTML.
/***************************************************************************/
void NoteHtmlWriter::_generateHtml(QTextStream& out, const Style& style, Note* note, int level) {

   QString sketchFilename;
   if ( (style.getSketchesEnabled())
         && (note->getEntry().getName() == "Sketch") ) {
      sketchFilename = _generateSketch(style, note);
   }

   if (style.getListViewType() == "tabled") {
      int depth = (_treeColumns - level) + 1;
      out << "<tr>";

      // Indent properly
      for (int j=0; j<level; j++) {
         out << "<td width=\"3%\"></td>";
      }
      out << endl;

      QString name = note->getName();
      name.replace(QRegExp("\\s"), "&nbsp;");
      out << "<td colspan=\"" << (depth + 2) << "\" valign=\"top\">";
      out << "<note id=\"" << note->getEntry().getName() << "\">"
            << name << "</note>" << endl;
      out << "</td>";
      out << "<td colspan=\"2\"></td>" << endl;
      out << "</tr>";

      if (note->getEntry().getName() == "Sketch") {
         out << "<tr>";
         out << "<td colspan=\"" << _treeColumns << "\"></td>" << endl;
         out << "<td align=\"right\" valign=\"top\">";
         out << "<property>Sketch</property>" << endl;
         out << "</td>";
         out << "<td width=\"90%\" valign=\"top\" >";
         out << "<data>";
         if (style.getSketchesEnabled()) {
            out << "<img border=\"1\" src=\"" << sketchFilename << "\"></img>";
         }
         out << "</data>" << endl;
         out << "</td>";
         out << "</tr>";
      }
      else {
         QString propName, propVal;
         for (size_t i=0; i<note->numPropertyValues(); i++) {
            propName = note->getEntry().getProperty(i).getName();
            propName.replace(QRegExp("\\s"), "&nbsp;");
            propVal = note->getPropertyValue(i).getValue();
            propVal.replace(QRegExp("[\\n\\r]"), "<br/>");
            if ((style.getNoBlankValues()) && (propVal.isEmpty()) ) {
               // don't print the blank value //
            }
            else {
               out << "<tr>";
               out << "<td colspan=\"" << _treeColumns << "\"></td>" << endl;
               out << "<td align=\"right\" valign=\"top\">";
               out << "<property>" << propName << "</property>" << endl;
               out << "</td>";
               out << "<td width=\"90%\" valign=\"top\" >";
               out << "<data>" << propVal << "</data>" << endl;
               out << "</td>";
               out << "</tr>";
            }
         }
      }

      Note* subNote = NULL;
      QPtrList<Note> subNoteList(note->getSubNotes());
      for (subNote=subNoteList.first(); subNote; subNote=subNoteList.next()) {
         _generateHtml(out, style, subNote, level+1);
      }
   }
   else if (style.getListViewType() == "bulleted") {
      out << "<note id=\"" << note->getEntry().getName() << "\">"
            << note->getName() << "</note>" << endl;

      out << "<ul>" << endl;
      if (note->getEntry().getName() == "Sketch") {
         out << "<li>" << endl;
         out << "<property>Sketch</property>" << endl;
         out << "<br/>";
         out << "<data>";
         if (style.getSketchesEnabled()) {
            out << "<img border=\"1\" src=\"" << sketchFilename << "\"></img>";
         }
         out << "</data>" << endl;
         out << "</li>" << endl;
      }
      else {
         QString propVal;
         for (size_t i=0; i<note->numPropertyValues(); i++) {
            propVal = note->getPropertyValue(i).getValue();
            if ((style.getNoBlankValues()) && (propVal.isEmpty()) ) {
               // don't print the blank value //
            }
            else {
               out << "<li>" << endl;
               out << "<property>" << note->getEntry().getProperty(i).getName()<< "</property>" << endl;
               out << "<br/>";
               out << "<data>" << propVal << "</data>" << endl;
               out << "</li>" << endl;
            }
         }
      }
      out << "</ul>" << endl;

      out << "<ul>" << endl;
      out << "<br/>" << endl;

      Note* subNote = NULL;
      QPtrList<Note> subNoteList(note->getSubNotes());
      for (subNote=subNoteList.first(); subNote; subNote=subNoteList.next()) {
         out << "<li>" << endl;
         _generateHtml(out, style, subNote, level+1);
         out << "</li>" << endl;
      }
      out << "</ul>" << endl;
   }
}



/***************************************************************************/
//! Generates an image sketch.
/***************************************************************************/
QString NoteHtmlWriter::_generateSketch(const Style& style, Note* note) {
   Strokes* strokes = new Strokes();

   QString basename, sketchFilename, propVal;
   basename = QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz");
   sketchFilename = style.getSketchDir() + QDir::separator() + basename + "." + style.getSketchFormat().lower();
   for (size_t i=0; i<note->numPropertyValues(); i++) {
      propVal = note->getPropertyValue(i).getValue();
      strokes->addStroke(propVal);
   }
   QPixmap pixmap(AppConst::SKETCH_WIDTH, AppConst::SKETCH_HEIGHT);
   pixmap.fill(Qt::white);
   QPainter painter(&pixmap);
   strokes->paint(&painter);
   if (!pixmap.save(sketchFilename, style.getSketchFormat())) {
      throw QString("Could not save sketch to a file (%1).").arg(sketchFilename);
   }

   delete strokes;

   QString relFilename(Environment::getRelativeDir(QDir(style.getSketchDir()), QDir(QFileInfo(_htmlFilePath).dirPath())));
   relFilename += QDir::separator() + basename + "." + style.getSketchFormat().lower();
   return relFilename;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void NoteHtmlWriter::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool NoteHtmlWriter::getDebug() const {
   return _debug;
}



