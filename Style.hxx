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
   \file    Style.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef STYLE_HXX
#define STYLE_HXX


#include <stdlib.h>

#include <qobject.h>

class QString;

/***************************************************************************/
/*!
   \class   Style
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class Style {
public:
   Style();
   ~Style();

   void setNoBlankValues(bool);
   bool getNoBlankValues() const;

   void setCleanTitle(bool);
   bool getCleanTitle() const;

   void setListViewType(const QString&);
   QString getListViewType() const;

   void setSketchesEnabled(bool);
   bool getSketchesEnabled() const;

   void setSketchDir(const QString&);
   QString getSketchDir() const;

   void setSketchFormat(const QString&);
   QString getSketchFormat() const;

protected:
   bool _noBlankValues;
   bool _cleanTitle;
   bool _sketchesEnabled;
   QString _listViewType;
   QString _sketchDir;
   QString _sketchFormat;

}; // end Style class


#endif
