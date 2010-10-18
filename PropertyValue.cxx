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
   \file    PropertyValue.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

#include <QString>

#include "PropertyValue.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
PropertyValue::PropertyValue() : _value(""), _debug(false) {
} // end constructor



/***************************************************************************/
//! Constructor
/***************************************************************************/
PropertyValue::PropertyValue(const QString& value) : _value(value), _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
PropertyValue::~PropertyValue() {
} // end destructor



/***************************************************************************/
//! Sets the object value.
/***************************************************************************/
void PropertyValue::setValue(const QString& value) {
   _value = value;
}



/***************************************************************************/
//! Returns the object value.
/***************************************************************************/
QString PropertyValue::getValue() const {
   return _value;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void PropertyValue::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool PropertyValue::getDebug() const {
   return _debug;
}



