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
   \file    PropertyXmlParser.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef PROPERTY_XML_PARSER_HXX
#define PROPERTY_XML_PARSER_HXX


#include <stdlib.h>

#include <qdom.h>
#include <qobject.h>

#include "Property.hxx"

class QString;

/***************************************************************************/
/*!
   \class   PropertyXmlParser
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class PropertyXmlParser {
public:
   PropertyXmlParser();
   ~PropertyXmlParser();

   void setDebug(bool);
   bool getDebug() const;

   Property parse(const QDomElement&);

protected:
   bool _debug;
}; // end PropertyXmlParser class


#endif
