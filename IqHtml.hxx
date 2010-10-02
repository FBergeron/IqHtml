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
   \file    IqHtml.hxx
   \author  James Bernsen
   \date    2003-01-24
*/
/***************************************************************************/

#ifndef IQ_HTML_HXX
#define IQ_HTML_HXX


#include <stdlib.h>

#include <QObject>

#include "Entry.hxx"
#include "Note.hxx"
#include "Style.hxx"

class QString;

/***************************************************************************/
/*!
   \class   IqHtml
   \author  James Bernsen
   \date    2003-01-24
*/
/***************************************************************************/
class IqHtml {
public:
   IqHtml();
   ~IqHtml();

   void setDebug(bool);
   bool getDebug() const;

   void setInFilename(const QString&);
   QString getInFilename() const;

   void setOutFilename(const QString&);
   QString getOutFilename() const;

   Entry getEntry(const QString&) const throw (QString);

   void process(const Style&) throw (QString);

protected:
   QString _inFilename, _outFilename;
   bool _debug;
   QList<Entry> _entryList;
   QList<Note*> _noteList;

   int _getMaxNoteDepth();
   void _parseInput() throw (QString);
   void _generateOutput(const Style&) throw (QString);

}; // end IqHtml class


#endif
