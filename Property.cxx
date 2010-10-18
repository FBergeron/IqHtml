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
   \file    Property.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

#include <QString>

#include "Property.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
Property::Property() : _name(""), _type(""), _debug(false) {
} // end constructor



/***************************************************************************/
//! Constructor
/***************************************************************************/
Property::Property(const QString& name) : _name(name), _type(""), _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
Property::~Property() {
} // end destructor



/***************************************************************************/
//! Sets the object name.
/***************************************************************************/
void Property::setName(const QString& value) {
   _name = value;
}



/***************************************************************************/
//! Returns the object name.
/***************************************************************************/
QString Property::getName() const {
   return _name;
}



/***************************************************************************/
//! Sets the object type.
/***************************************************************************/
void Property::setType(const QString& value) {
   _type = value;
}



/***************************************************************************/
//! Returns the object type.
/***************************************************************************/
QString Property::getType() const {
   return _type;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void Property::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool Property::getDebug() const {
   return _debug;
}



