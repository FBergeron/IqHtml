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
   \file    IqHtml.cxx
   \author  James Bernsen
   \date    2002-01-24
*/
/***************************************************************************/

#include <iostream.h>

#include <qdom.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qglobal.h>
#include <qregexp.h>
#include <qstring.h>

#include "EntryXmlParser.hxx"
#include "IqHtml.hxx"
#include "NoteHtmlWriter.hxx"
#include "NoteXmlParser.hxx"


/***************************************************************************/
template <class T>
inline const T& max(const T& left, const T& right) {
   return (left > right) ? left : right;
}
/***************************************************************************/


/***************************************************************************/
//! Constructor
/***************************************************************************/
IqHtml::IqHtml() : _debug(false) {
   _noteList.setAutoDelete(true);

   Entry textEntry("Text");
   Property textProperty("Text");
   textProperty.setType("multiLine");
   textEntry.setProperty(textProperty);
   _entryList.push_back(textEntry);

   Entry sketchEntry("Sketch");
   _entryList.push_back(sketchEntry);
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
IqHtml::~IqHtml() {
} // end destructor



/***************************************************************************/
//! Sets the input filename.
/***************************************************************************/
void IqHtml::setInFilename(const QString& value) {
   _inFilename = value;
}



/***************************************************************************/
//! Returns the input filename.
/***************************************************************************/
QString IqHtml::getInFilename() const {
   return _inFilename;
}



/***************************************************************************/
//! Sets the output filename.
/***************************************************************************/
void IqHtml::setOutFilename(const QString& value) {
   _outFilename = value;
}



/***************************************************************************/
//! Returns the output filename.
/***************************************************************************/
QString IqHtml::getOutFilename() const {
   return _outFilename;
}



/***************************************************************************/
//! Processes the XML input into HTML output.
/***************************************************************************/
void IqHtml::process(const Style& style) throw (QString) {
   _parseInput();
   _generateOutput(style);
}



/***************************************************************************/
//! Parses the input file.
/***************************************************************************/
void IqHtml::_parseInput() throw (QString) {
   QDomDocument doc("inputfile");
   QFile file(_inFilename);
   if (!file.open(IO_ReadOnly)) {
      QString errMsg( QString("Could not open file (%1) for reading.").arg(_inFilename) );
      throw QString(errMsg);
   }
   if (!doc.setContent(&file)) {
      file.close();
      QString errMsg( QString("Could not parse file (%1) content as XML.").arg(_inFilename) );
      throw QString(errMsg);
   }
   file.close();

   QDomElement docElem = doc.documentElement();
   QDomNode node = docElem.firstChild();
   while( !node.isNull() ) {
      QDomElement elem = node.toElement();
      if( !elem.isNull() ) {
         if (elem.tagName().lower() == "entries") {
            QDomNode innerNode = elem.firstChild();
            while (!innerNode.isNull() ) {
               QDomElement innerElem = innerNode.toElement();
               if (!innerElem.isNull()) {
                  if (innerElem.tagName().lower() == "entry") {
                     EntryXmlParser entryXmlParser;
                     entryXmlParser.setDebug(getDebug());
                     _entryList.push_back(entryXmlParser.parse(innerElem));
                  }
               }
               innerNode = innerNode.nextSibling();
            }
         }
         if (elem.tagName().lower() == "notes") {
            QDomNode innerNode = elem.firstChild();
            while (!innerNode.isNull() ) {
               QDomElement innerElem = innerNode.toElement();
               if (!innerElem.isNull()) {
                  if (innerElem.tagName().lower() == "note") {
                     NoteXmlParser noteXmlParser;
                     noteXmlParser.setDebug(getDebug());
                     _noteList.append(noteXmlParser.parse(innerElem, this));
                  }
               }
               innerNode = innerNode.nextSibling();
            }
         }
      }
      node = node.nextSibling();
   }
}



/***************************************************************************/
//! Generates HTML output.
/***************************************************************************/
void IqHtml::_generateOutput(const Style& style) throw (QString) {

   QFile file(_outFilename);

   if (!file.open(IO_WriteOnly)) {
      throw QString( QString("Could not open file (%1) for writing.").arg(_outFilename) );
   }

   QString title = QFileInfo(_inFilename).fileName();

   if (style.getCleanTitle()) {
      title.replace(QRegExp("\\.xml$"), "");
      title.replace("_", " ");
   }

   QTextStream out(&file);
   out << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>" << endl;
   out << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" << endl;
   out << "<html xmlns=\"http://www.w3.org/1999/xhtml\">" << endl;
   out << "<head>" << endl;
   out << "<title>" << title << "</title>" << endl;
   out << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\" />" << endl;
   out << "<link href=\"iqnotes.css\" rel=\"stylesheet\" type=\"text/css\">" << endl;
   out << "</head>" << endl;
   out << "<body>" << endl;

   out << "<h1>" << title << "</h1>" << endl;

   NoteHtmlWriter noteHtmlWriter;
   noteHtmlWriter.setDebug(getDebug());
   Note* note;
   int maxDepth = _getMaxNoteDepth();

   if (style.getListViewType() == "tabled") {
      out << "<table width=\"100%\" border=\"0\" cellspacing=\"0\" cellpadding=\"5\">" << endl;
      for (note=_noteList.first(); note; note=_noteList.next()) {
         noteHtmlWriter.generateHtml(out, _outFilename, style, note, maxDepth);
      }
      out << "</table>" << endl;
   }
   else if (style.getListViewType() == "bulleted") {
      out << "<ul>" << endl;
      for (note=_noteList.first(); note; note=_noteList.next()) {
         out << "<li>" << endl;
         noteHtmlWriter.generateHtml(out, _outFilename, style, note, maxDepth);
         out << "</li>" << endl;
      }
      out << "</ul>" << endl;
   }

   out << "</body>" << endl;
   out << "</html>" << endl;

   file.close();
}



/***************************************************************************/
//! Returns the entry by this name.
/***************************************************************************/
Entry IqHtml::getEntry(const QString& name) const throw (QString) {
   QValueList<Entry>::const_iterator iter;
   for (iter=_entryList.begin(); iter!=_entryList.end(); iter++) {
      if ((*iter).getName() == name) {
         return (*iter);
      }
   }

   // throw QString("Unknown entry type (%1) encountered.").arg(name));

   return Entry();
}



/***************************************************************************/
/*
   \brief   Returns the maximum depth of children.
   \note    A note with no child notes would have a depth of zero.
*/
/***************************************************************************/
int IqHtml::_getMaxNoteDepth() {
   Note* note;
   int maxDepth=0, depth=0;
   for (note=_noteList.first(); note; note=_noteList.next()) {
      depth = (note->getMaxChildDepth() + 1);
      maxDepth = max(depth, maxDepth);
   }
   return maxDepth;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void IqHtml::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool IqHtml::getDebug() const {
   return _debug;
}



