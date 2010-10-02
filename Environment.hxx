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
   \file    Environment.hxx
   \author  James Bernsen
   \date    2002-06-11
   \brief   Contains class definition for Environment class.

   This file contains the class definition for the Environment class.

   \sa Environment.cxx
*/
/***************************************************************************/


#ifndef ENVIRONMENT_HXX
#define ENVIRONMENT_HXX

#include <QMap>
#include <QString>
#include <QStringList>

/***************************************************************************/
/*!
   \class   Environment
   \brief   Class to provide information on the system and environment.
   \author  James Bernsen
   \date    2002-06-18

   This class contains helper functions.
*/
/***************************************************************************/
class Environment {

public:
   Environment();
   ~Environment();

   typedef QMap<QString, QString> ArgMap;
   typedef QMap<QString, QStringList> CfgMap;

   static ArgMap  getArgMap(int&, char**argv, const QStringList&) throw(QString);

   static QString getRelativeDir(const QDir& in, const QDir& relativeTo=QDir::current());

protected:
   enum ArgType {
      LONER_ARGUMENT,
      PARAM_IGNORED,
      PARAM_REQUIRED,
      PARAM_OPTIONAL,
      ARG_AND_PARAM_REQUIRED
   };

   static void _removeArg(int&, char**argv, int argn) throw();
   static QString _getDrive(const QDir&);
   static QString _normalizePath(const QString&);
   static QStringList _splitDir(const QDir&);


}; // end class Environment //

#endif // end ENVIRONMENT_HXX
