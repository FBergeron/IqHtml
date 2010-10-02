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
    \file   const.hxx
    \brief  Global constants used throughout the application.
    \author James Bernsen
    \date   2003-09-25
*/
/***************************************************************************/


#ifndef CONST_HXX
#define CONST_HXX

#include <qstring.h>


/***************************************************************************/
/*!
   \class   AppConst
   \brief   Encapsulates application constants.
   \author  James Bernsen
   \date    2003-09-30
*/
/***************************************************************************/
class AppConst {
public:
   static const QString APPLICATION_TITLE;
   static const QString APPLICATION_WEBSITE;

   static const int MAJOR_VERSION;
   static const int MINOR_VERSION;
   static const int REVISION_NUMBER;

   static const int SKETCH_WIDTH;
   static const int SKETCH_HEIGHT;
};





#endif // end CONST_HXX
