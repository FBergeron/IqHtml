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
   \file    NoteHtmlWriter.hxx
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/

#ifndef NOTE_HTML_WRITER_HXX
#define NOTE_HTML_WRITER_HXX


#include <stdlib.h>

#include <qobject.h>

#include "Note.hxx"
#include "Style.hxx"

class QString;

/***************************************************************************/
/*!
   \class   NoteHtmlWriter
   \author  James Bernsen
   \date    2003-09-26
*/
/***************************************************************************/
class NoteHtmlWriter {
public:
   NoteHtmlWriter();
   ~NoteHtmlWriter();

   void generateHtml(QTextStream&, const QString&, const Style&, Note*, int);

   void setDebug(bool);
   bool getDebug() const;

protected:
   void _generateHtml(QTextStream&, const Style&, Note*, int);
   QString _generateSketch(const Style&, Note*);

   QString _htmlFilePath;
   int _treeColumns;
   bool _debug;
}; // end NoteHtmlWriter class


#endif
