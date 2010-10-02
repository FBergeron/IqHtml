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
   \file    Const.cxx
   \author  James Bernsen
   \date    2003-09-30
   \brief   Contains constants for this application.

   By placing application-level constants in a class, we don't need to
   recompile every source file when a constant value is changed.

   \sa const.hxx
*/
/***************************************************************************/


#include "const.hxx"


const QString AppConst::APPLICATION_TITLE = "IqHtml";
const QString AppConst::APPLICATION_WEBSITE = "http://www.bernsen.us/james/software/IqHtml";


/***************************************************************************/
/*!
   \name    Version Info
            Defines the version/revision of this product
*/
/***************************************************************************/
//@{
const int AppConst::MAJOR_VERSION    = 1;
const int AppConst::MINOR_VERSION    = 0;
const int AppConst::REVISION_NUMBER  = 1;
//@}


/***************************************************************************/
/*!
   \name    Sketch information.
            Specifies the size of a sketch.
*/
/***************************************************************************/
//@{
const int AppConst::SKETCH_WIDTH = 238;
const int AppConst::SKETCH_HEIGHT = 245;
//@}

