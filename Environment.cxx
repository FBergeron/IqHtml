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
   \file    Environment.cxx
   \brief   Class to provide information about the system and environment.
   \author  James Bernsen
   \date    2002-06-18

   This class contains helper functions.

   \sa      Environment.hxx
*/
/***************************************************************************/

#include <stdlib.h>

#include <qglobal.h>

#ifdef Q_WS_WIN
   #include <windows.h>
   #include <winbase.h>
   #include <winnls.h>
   #include <lm.h>
   #include <LMCONS.H>
   #include <process.h>
#else
   #include <netdb.h>
   #include <unistd.h>
   #include <pwd.h>
   #include <sys/types.h>
   #include <sys/wait.h>
   #include <sys/utsname.h>
   #include <errno.h>
#endif

#include <qdir.h>
#include <qfileinfo.h>
#include <qregexp.h>

#include "Environment.hxx"



/***************************************************************************/
//! Constructor
/***************************************************************************/
Environment::Environment() {
}


/***************************************************************************/
//! Destructor
/***************************************************************************/
Environment::~Environment() {
}



/***************************************************************************/
//! This routine effectively removes an argument (argn) from the list and
//! decrements argc.
/***************************************************************************/
void Environment::_removeArg(int &argc, char **argv, int argn) throw() {
   int i;

   for(i=argn; i<(argc-1); i++) {
      argv[i] = argv[i+1];
   }
   argv[argc-1]=0;
   argc--;
}



/***************************************************************************/
/***************************************************************************/
Environment::ArgMap Environment::getArgMap(int &argc, char **argv,
      const QStringList &recognizedArgs) throw (QString) {

   QStringList argList;
   for (int i=0; i<argc; i++) {
      argList.push_back(argv[i]);
   }

   QStringList recognized = recognizedArgs;
   QStringList::iterator listIter;

   QRegExp lonerArgument("(\\-\\w+)\\*");
   QRegExp paramIgnored("(\\-\\w+)");
   QRegExp paramOptional("(\\-\\w+)\\?");
   QRegExp paramRequired("(\\-\\w+):");
   QRegExp argAndParamRequired("(\\-\\w+)!");

   QStringList lonerArgsFound, argsNotFound, paramsNotFound;

   QMap<QString, Environment::ArgType> argInfo;
   QMap<QString, Environment::ArgType> ::iterator mapIter;

   ArgMap argMap;

   QString argument, parameter;

   // Create the argInfo map //
   for(listIter=recognized.begin(); listIter!=recognized.end(); listIter++) {
      if (lonerArgument.exactMatch(*listIter) ) {
         argument = lonerArgument.cap(1);
         argInfo[argument] = LONER_ARGUMENT;
      }
      else if (paramIgnored.exactMatch(*listIter) ) {
         argument = paramIgnored.cap(1);
         argInfo[argument] = PARAM_IGNORED;
      }
      else if (paramOptional.exactMatch(*listIter) ) {
         argument = paramOptional.cap(1);
         argInfo[argument] = PARAM_OPTIONAL;
      }
      else if (paramRequired.exactMatch(*listIter) ) {
         argument = paramRequired.cap(1);
         argInfo[argument] = PARAM_REQUIRED;
      }
      else if (argAndParamRequired.exactMatch(*listIter) ) {
         argument = argAndParamRequired.cap(1);
         argInfo[argument] = ARG_AND_PARAM_REQUIRED;
      }
      else {
         QString errmsg("Invalid recognition format (" + (*listIter) + ") encountered.");
         throw QString(errmsg);
      }
   }


   size_t argNum=0;
   int argn=0;
   while(argNum<argList.size()) {
      argument = argList[argNum];

      if (argInfo.find(argument) == argInfo.end()) {
         // The argument is not recognized. //
         argNum++;
         argn++;
      }
      else {
         // The argument is recognized. //
         _removeArg(argc, argv, argn);

         switch(argInfo[argument]) {
            case(LONER_ARGUMENT): {
               argNum++;
               argMap[argument] = QString::null;
               lonerArgsFound += argument;
               break;
            }
            case(PARAM_IGNORED): {
               argNum++;
               argMap[argument] = QString::null;
               break;
            }
            case (PARAM_OPTIONAL): {
               argNum++;
               argMap[argument] = QString::null;
               if (argNum<argList.count()) {
                  // there is another argument //
                  if (argInfo.find(argList[argNum]) == argInfo.end()) {
                     // The next argument is not in the recognized  //
                     // list, so it must be the optional parameter. //
                     parameter = argList[argNum];
                     argMap[argument] = parameter;
                     argNum++;

                     // remove the item from argv and decrement argc //
                     _removeArg(argc, argv, argn);
                  }
               }
               break;
            }
            case (PARAM_REQUIRED):
            case (ARG_AND_PARAM_REQUIRED): {
               argNum++;
               if (argNum<argList.count()) {
                  if (argInfo.find(argList[argNum]) == argInfo.end()) {
                     // The next argument is not in the recognized  //
                     // list, so it must be the required parameter. //
                     parameter = argList[argNum];
                     argMap[argument] = parameter;
                     argNum++;

                     // remove the item from argv and decrement argc //
                     _removeArg(argc, argv, argn);
                  }
                  else {
                     paramsNotFound.push_back(argument);
                  }
               }
               else {
                  paramsNotFound.push_back(argument);
               }
               break;
            }
            default: {
               throw QString("Unknown argInfo value.");
            }

         }  // end switch (argInfo[argument])

      } // end if parameter recognized

   } // end while

   for (mapIter=argInfo.begin(); mapIter!=argInfo.end(); mapIter++) {
      if ( (mapIter.value() == ARG_AND_PARAM_REQUIRED) &&
            (argMap.find(mapIter.key()) == argMap.end() ) ) {
         argsNotFound.push_back(mapIter.key());
      }
   }

   if (lonerArgsFound.count() > 1) {
      QString errmsg("The following arguments (");

      for (listIter=lonerArgsFound.begin(); listIter!=lonerArgsFound.end(); listIter++) {
         if (listIter != lonerArgsFound.begin()) errmsg += ", ";
         errmsg += "\"" + (*listIter) + "\"";
      }

      errmsg += ") are mutually exclusive.  Only one can be used.";
      throw QString(errmsg);
   }

   if ( (argsNotFound.count() > 0) && (lonerArgsFound.count() == 0) ) {
      QString errmsg("One or more of the required arguments (");

      for (listIter=argsNotFound.begin(); listIter!=argsNotFound.end(); listIter++) {
         if (listIter != argsNotFound.begin()) errmsg += ", ";
         errmsg += "\"" + (*listIter) + "\"";
      }

      errmsg += ") was not found.";
      throw QString(errmsg);
   }

   if ( (paramsNotFound.count() > 0) && (lonerArgsFound.count() == 0) ){
      QString errmsg("One or more of the arguments that require a parameter (");

      for (listIter=paramsNotFound.begin(); listIter!=paramsNotFound.end(); listIter++) {
         if (listIter != paramsNotFound.begin()) errmsg += ", ";
         errmsg += "\"" + (*listIter) + "\"";
      }

      errmsg += ") did not have a parameter supplied.";
      throw QString(errmsg);
   }

   return argMap;
}



/***************************************************************************/
/** return the directory path of 'in' relative to 'relativeTo'
    e.g. if in = "/x/y/z" and relative to = "/x/a" return "../../a/"
 */
/***************************************************************************/
QString Environment::getRelativeDir(const QDir & in, const QDir & relativeTo) {
   QDir inDir( in.absolutePath() );
   QDir relDir( relativeTo.absolutePath() );

   if ( _getDrive( inDir ) != _getDrive( relDir ) ) {
      // drives don't match, so relative path not possible
      return inDir.absolutePath() + "/";
   }

   if ( _normalizePath(inDir.absolutePath()) == _normalizePath(relDir.absolutePath()) ) {
      // same dir
      return QString::null;
   }

   QStringList inDirElements = _splitDir( inDir );
   QStringList relDirElements = _splitDir( relDir );

   int checkDepth = inDirElements.count() < relDirElements.count() ? inDirElements.count() : relDirElements.count();
   int matchDepth = 0;
   for ( int i = 0; i < checkDepth; i++ ) {
      //if ( *inDirElements.at( i ) != *relDirElements.at( i ) )
      if ( inDirElements.at( i ) != relDirElements.at( i ) )
         break;
      else
         matchDepth = i + 1;
   } // directory elements equal to depth matchDepth

   QString ret;

   // go up to common dir
   for ( unsigned int j = 0; j < relDirElements.count() - matchDepth; j++ ) {
      ret += "../";
   }

   // go down to in dir
   for ( unsigned int k = 0; k < inDirElements.count() - matchDepth; k++ ) {
      //ret += *inDirElements.at( matchDepth + k ) + "/";
      ret += inDirElements.at( matchDepth + k ) + "/";
   }

   return ret;
}


/***************************************************************************/
/*!
   \brief   Normalizes a path so that it can be compared.
*/
/***************************************************************************/
QString Environment::_normalizePath(const QString& origPath) {
   QString normalPath = QDir::cleanPath(origPath);
   normalPath = QDir::convertSeparators(normalPath);

#ifdef Q_WS_WIN
   normalPath = normalPath.toUpper();
#endif

   return normalPath;
}


/***************************************************************************/
//! Return the drive letter of a path.
/***************************************************************************/
QString Environment::_getDrive(const QDir& dir) {
   QString path(_normalizePath(dir.absolutePath()));
   QString drive("");
   if (path.at(1) == ':') {
      drive = path.left(1).toUpper();
   }
   return drive;
}


/***************************************************************************/
//! Splits a path into directory components.
/***************************************************************************/
QStringList Environment::_splitDir(const QDir& dir) {
   QString path = _normalizePath(dir.absolutePath());
   QStringList dirList;
   dirList = path.split( QDir::separator() );
   return dirList;
}


