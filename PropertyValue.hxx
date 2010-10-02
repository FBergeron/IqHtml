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
   \file    PropertyValue.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef PROPERTY_VALUE_HXX
#define PROPERTY_VALUE_HXX


#include <stdlib.h>

class QString;

/***************************************************************************/
/*!
   \class   PropertyValue
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class PropertyValue {
public:
   PropertyValue();
   PropertyValue(const QString&);
   ~PropertyValue();

   void setValue(const QString&);
   QString getValue() const;

   void setDebug(bool);
   bool getDebug() const;

protected:
   QString _value;
   bool _debug;
}; // end PropertyValue class


#endif
