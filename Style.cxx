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
   \file    Style.cxx
   \author  James Bernsen
   \date    2002-09-26
*/
/***************************************************************************/

#include <iostream.h>

#include <qglobal.h>
#include <qstring.h>

#include "Style.hxx"


/***************************************************************************/
//! Constructor
/***************************************************************************/
Style::Style() : _noBlankValues(false) {
} // end constructor



/***************************************************************************/
//! Destructor
/***************************************************************************/
Style::~Style() {
} // end destructor



/***************************************************************************/
//! Indicates whether or not blank property values should be printed.
/***************************************************************************/
void Style::setNoBlankValues(bool value) {
   _noBlankValues = value;
}



/***************************************************************************/
//! Indicates whether or not blank property values should be printed.
/***************************************************************************/
bool Style::getNoBlankValues() const {
   return _noBlankValues;
}



/***************************************************************************/
/*
   \brief   Indicates whether or not the input filename should be cleaned
            up when used as a title.
*/
/***************************************************************************/
void Style::setCleanTitle(bool value) {
   _cleanTitle = value;
}



/***************************************************************************/
/*
   \brief   Indicates whether or not the input filename should be cleaned
            up when used as a title.
*/
/***************************************************************************/
bool Style::getCleanTitle() const {
   return _cleanTitle;
}



/***************************************************************************/
/*
   \brief   Indicates whether notes should be displayed in a bulleted
            or a tabled format.
   \note    Valid values are "bulleted" or "tabled".
*/
/***************************************************************************/
void Style::setListViewType(const QString& value) {
   _listViewType = value;
}



/***************************************************************************/
/*
   \brief   Indicates whether notes should be displayed in a bulleted
            or a tabled format.
   \note    Valid values are "bulleted" or "tabled".
*/
/***************************************************************************/
QString Style::getListViewType() const {
   return _listViewType;
}



/***************************************************************************/
/*
   \brief   Indicates whether or not sketch creation is enabled.
*/
/***************************************************************************/
void Style::setSketchesEnabled(bool value) {
   _sketchesEnabled = value;
}



/***************************************************************************/
/*
   \brief   Indicates whether or not sketch creation is enabled.
*/
/***************************************************************************/
bool Style::getSketchesEnabled() const {
   return _sketchesEnabled;
}



/***************************************************************************/
/*
   \brief   Indicates the directory where sketch images are stored.
*/
/***************************************************************************/
void Style::setSketchDir(const QString& value) {
   _sketchDir = value;
}



/***************************************************************************/
/*
   \brief   Indicates the directory where sketch images are stored.
*/
/***************************************************************************/
QString Style::getSketchDir() const {
   return _sketchDir;
}



/***************************************************************************/
/*
   \brief   Indicates the file format for sketch images.
*/
/***************************************************************************/
void Style::setSketchFormat(const QString& value) {
   _sketchFormat = value;
}



/***************************************************************************/
/*
   \brief   Indicates the file format for sketch images.
*/
/***************************************************************************/
QString Style::getSketchFormat() const {
   return _sketchFormat;
}



