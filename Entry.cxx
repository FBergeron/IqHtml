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
   \file    Entry.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

#include <QString>

#include "Entry.hxx"

using namespace std;

/***************************************************************************/
//! Constructor
/***************************************************************************/
Entry::Entry() : _name(""), _debug(false) {
} // end constructor



/***************************************************************************/
//! Constructor
/***************************************************************************/
Entry::Entry(const QString& name) : _name(name), _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
Entry::~Entry() {
} // end destructor



/***************************************************************************/
//! Sets the object name.
/***************************************************************************/
void Entry::setName(const QString& value) {
   _name = value;
}



/***************************************************************************/
//! Returns the object name.
/***************************************************************************/
QString Entry::getName() const {
   return _name;
}



/***************************************************************************/
//! Sets the object properties.
/***************************************************************************/
void Entry::setProperties(const QList<Property>& vecProp) {
   _properties = vecProp;
}



/***************************************************************************/
//! Returns the object properties.
/***************************************************************************/
QList<Property> Entry::getProperties() const {
   return _properties;
}



/***************************************************************************/
//! Sets a single object property.
/***************************************************************************/
void Entry::setProperty(const Property& prop, size_t index) {
   if (index == -1) {
      _properties.push_back(prop);
   }
   else {
      if (_properties.size() <= (index+1))
          _properties.append( prop );
      else
          _properties[index] = prop;
   }
}



/***************************************************************************/
//! Returns an object property.
/***************************************************************************/
Property Entry::getProperty(size_t index) const {
   if (_properties.size() >= (index+1)) {
      return _properties.at(index);
   }

   return Property();
}



/***************************************************************************/
//! Returns the number of properties on this entry.
/***************************************************************************/
size_t Entry::numProperties() const {
   return _properties.count();
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void Entry::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool Entry::getDebug() const {
   return _debug;
}



