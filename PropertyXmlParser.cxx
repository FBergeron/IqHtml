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
   \file    PropertyXmlParser.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

#include <QString>

#include "PropertyXmlParser.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
PropertyXmlParser::PropertyXmlParser() : _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
PropertyXmlParser::~PropertyXmlParser() {
} // end destructor



/***************************************************************************/
//! Sets the object node.
/***************************************************************************/
Property PropertyXmlParser::parse(const QDomElement& elmProperty) {
   Property property;

   if (elmProperty.isNull()) return property;
   if (elmProperty.tagName().toLower() != "property") return property;

   if (getDebug()) qDebug( qPrintable( QString("PROPERTY: name(%1) type(%2)").arg(elmProperty.attribute("name")).arg(elmProperty.attribute("type")) ) );

   property.setName(elmProperty.attribute("name"));
   property.setType(elmProperty.attribute("type"));

   return property;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void PropertyXmlParser::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool PropertyXmlParser::getDebug() const {
   return _debug;
}



