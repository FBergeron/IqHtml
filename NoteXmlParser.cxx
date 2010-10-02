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
   \file    NoteXmlParser.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

//#include <QGlobal>
#include <QString>

#include "IqHtml.hxx"
#include "NoteXmlParser.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
NoteXmlParser::NoteXmlParser() : _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
NoteXmlParser::~NoteXmlParser() {
} // end destructor



/***************************************************************************/
/*
   \brief   Parses the object node.
   \note    Caller is responsible for deleting returned object.
*/
/***************************************************************************/
Note* NoteXmlParser::parse(const QDomElement& elmNote, IqHtml* iqHtml) throw (QString) {
   Note *note = NULL;

   if (elmNote.isNull()) return note;
   if (elmNote.tagName().toLower() != "note") return note;

   if (getDebug()) qDebug( qPrintable( QString("NOTE: name(%1) type(%2)").arg(elmNote.attribute("name")).arg(elmNote.attribute("type")) ) );

   note = new Note(elmNote.attribute("name"));

   Entry entry;
   entry = iqHtml->getEntry(elmNote.attribute("type"));
   note->setEntry(entry);

   QString propPrefix;
   if (entry.getName() == "Sketch") {
      propPrefix = "stroke";
   }
   else {
      propPrefix = "data";
   }

   int i=0;
   while (true) {
      QString attrName, value;
      attrName = QString("%1%2").arg(propPrefix).arg(i);
      if (!elmNote.hasAttribute(attrName)) break;

      value = elmNote.attribute(attrName);
      PropertyValue propVal(value);
      note->setPropertyValue(propVal, i);
      if (getDebug()) qDebug( qPrintable( QString("   DATA: %1(%2)").arg(attrName).arg(elmNote.attribute(attrName)) ) );
      i++;
   }

   QDomNode node = elmNote.firstChild();
   while (!node.isNull()) {
      QDomElement elem = node.toElement();
      if (!elem.isNull()) {
         if (elem.tagName().toLower() == "note") {
            NoteXmlParser noteXmlParser;
            noteXmlParser.setDebug(getDebug());
            note->addSubNote(noteXmlParser.parse(elem, iqHtml));
         }
      }
      node = node.nextSibling();
   }
   return note;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void NoteXmlParser::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool NoteXmlParser::getDebug() const {
   return _debug;
}



