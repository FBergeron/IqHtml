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
   \file    Entry.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef ENTRY_HXX
#define ENTRY_HXX


#include <stdlib.h>

#include <QObject>
#include <QList>

#include "Property.hxx"

class QString;

/***************************************************************************/
/*!
   \class   Entry
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class Entry {
public:
   Entry();
   Entry(const QString&);
   ~Entry();

   void setName(const QString&);
   QString getName() const;

   void setProperties(const QList<Property>&);
   void setProperty(const Property&, size_t=-1);
   QList<Property> getProperties() const;
   Property getProperty(size_t) const;
   size_t numProperties() const;

   void setDebug(bool);
   bool getDebug() const;

protected:
   QString _name;
   QList<Property> _properties;
   bool _debug;
}; // end Entry class


#endif
