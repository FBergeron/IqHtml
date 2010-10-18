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
   \file    EntryXmlParser.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

#include <QString>

#include "EntryXmlParser.hxx"
#include "PropertyXmlParser.hxx"

/***************************************************************************/
//! Constructor
/***************************************************************************/
EntryXmlParser::EntryXmlParser() : _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
EntryXmlParser::~EntryXmlParser() {
} // end destructor



/***************************************************************************/
//! Sets the object node.
/***************************************************************************/
Entry EntryXmlParser::parse(const QDomElement& elmEntry) {
   Entry entry;

   if (elmEntry.isNull()) return entry;
   if (elmEntry.tagName().toLower() != "entry") return entry;

   if (getDebug()) qDebug( qPrintable( QString("ENTRY: name(%1)").arg(elmEntry.attribute("name")) ) );

   entry.setName(elmEntry.attribute("name"));

   QDomNode node = elmEntry.firstChild();
   while (!node.isNull()) {
      QDomElement elem = node.toElement();
      if (!elem.isNull()) {
         if (elem.tagName().toLower() == "property") {
            PropertyXmlParser propertyXmlParser;
            propertyXmlParser.setDebug(getDebug());
            entry.setProperty(propertyXmlParser.parse(elem));
         }
      }
      node = node.nextSibling();
   }

   if (getDebug()) qDebug( qPrintable( QString("(Total properties: %1)").arg(entry.numProperties()) ) );

   return entry;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void EntryXmlParser::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool EntryXmlParser::getDebug() const {
   return _debug;
}



