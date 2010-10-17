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
   \file    Note.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream>

//#include <qglobal.h>
#include <QString>

#include "Note.hxx"


/***************************************************************************/
template <class T>
inline const T& max(const T& left, const T& right) {
   return (left > right) ? left : right;
}
/***************************************************************************/


/***************************************************************************/
//! Constructor
/***************************************************************************/
Note::Note() : _name(""), _entry(NULL), _debug(false) {
} // end constructor



/***************************************************************************/
//! Constructor
/***************************************************************************/
Note::Note(const QString& name) : _name(name), _entry(NULL), _debug(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
Note::~Note() {
   // The setAutoDelete() method is not available anymore in the API so comment the following line out. - FB
   //_subNotes.setAutoDelete(true);
} // end destructor



/***************************************************************************/
//! Sets the object name.
/***************************************************************************/
void Note::setName(const QString& value) {
   _name = value;
}



/***************************************************************************/
//! Returns the object name.
/***************************************************************************/
QString Note::getName() const {
   return _name;
}



/***************************************************************************/
//! Sets the object entry type.
/***************************************************************************/
void Note::setEntry(const Entry& value) {
   _entry = value;
}



/***************************************************************************/
//! Returns the object entry type.
/***************************************************************************/
Entry Note::getEntry() const {
   return _entry;
}



/***************************************************************************/
//! Sets the object propertyValues.
/***************************************************************************/
void Note::setPropertyValues(const QList<PropertyValue>& vecProp) {
   _propertyValues = vecProp;
}



/***************************************************************************/
//! Returns the object propertyValues.
/***************************************************************************/
QList<PropertyValue> Note::getPropertyValues() const {
   return _propertyValues;
}



/***************************************************************************/
//! Sets a single object property.
/***************************************************************************/
void Note::setPropertyValue(const PropertyValue& prop, size_t index) {
   if (index == -1) {
      _propertyValues.push_back(prop);
   }
   else {
      if (_propertyValues.size() <= (index+1)) 
        _propertyValues.append( prop );
      else 
        _propertyValues[index] = prop;
   }
}



/***************************************************************************/
//! Returns an object property.
/***************************************************************************/
PropertyValue Note::getPropertyValue(size_t index) const {
   if (_propertyValues.size() >= (index+1)) {
      return _propertyValues.at(index);
   }

   return PropertyValue();
}



/***************************************************************************/
//! Returns the number of property values on this entry.
/***************************************************************************/
size_t Note::numPropertyValues() const {
   return _propertyValues.count();
}



/***************************************************************************/
/*
   \brief   Adds a subnote to this note.
   \note    This note object is now responsible for the deletion of the
            specified subnote.  Caller should not delete the subnote.
*/
/***************************************************************************/
void Note::addSubNote(Note* note) {
   _subNotes.append(note);
}



/***************************************************************************/
/*
   \brief   Returns a copy of the pointer list (not a copy of the actual
            values, so do not delete them) of this notes sub-notes.
*/
/***************************************************************************/
QList<Note*> Note::getSubNotes() const {
   return _subNotes;
}



/***************************************************************************/
/*
   \brief   Returns the maximum depth of children.
   \note    A note with no child notes would have a depth of zero.
*/
/***************************************************************************/
int Note::getMaxChildDepth() {
   int maxDepth=0, depth=0;
   for (QList<Note*>::iterator it = _subNotes.begin(); it != _subNotes.end(); ++it ) {
      Note* note = *it;
      depth = (note->getMaxChildDepth() + 1);
      maxDepth = ( depth > maxDepth ? depth : maxDepth );
   }
   return maxDepth;
}



/***************************************************************************/
//! Sets the debugging mode.
/***************************************************************************/
void Note::setDebug(bool value) {
   _debug = value;
}



/***************************************************************************/
//! Returns the debugging mode.
/***************************************************************************/
bool Note::getDebug() const {
   return _debug;
}



