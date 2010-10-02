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
   \file    Note.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef NOTE_HXX
#define NOTE_HXX


#include <stdlib.h>

#include <qobject.h>
#include <qptrlist.h>

#include "Entry.hxx"
#include "PropertyValue.hxx"

class QString;

/***************************************************************************/
/*!
   \class   Note
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class Note {
public:
   Note();
   Note(const QString&);
   ~Note();

   void setName(const QString&);
   QString getName() const;

   void setEntry(const Entry&);
   Entry getEntry() const;

   void setPropertyValues(const QValueVector<PropertyValue>&);
   void setPropertyValue(const PropertyValue&, size_t=-1);
   QValueVector<PropertyValue> getPropertyValues() const;
   PropertyValue getPropertyValue(size_t) const;
   size_t numPropertyValues() const;

   void addSubNote(Note*);
   QPtrList<Note> getSubNotes() const;

   int getMaxChildDepth();

   void setDebug(bool);
   bool getDebug() const;

protected:
   QString _name;
   Entry _entry;
   QValueVector<PropertyValue> _propertyValues;
   QPtrList<Note> _subNotes;
   bool _debug;
}; // end Note class


#endif
