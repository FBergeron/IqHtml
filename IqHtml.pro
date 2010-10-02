#############################################################################
## Copyright (C) 2000 by Lexmark International Inc.
## All rights reserved.   Internal Use Only
#############################################################################

TEMPLATE =  app

CONFIG   += qt warn_on console debug thread

SOURCES  += const.cxx \
            main.cxx \
            qsketch.cpp \
            Entry.cxx \
            EntryXmlParser.cxx \
            Environment.cxx \
            IqHtml.cxx \
            Note.cxx \
            NoteHtmlWriter.cxx \
            NoteXmlParser.cxx \
            Property.cxx \
            PropertyValue.cxx \
            PropertyXmlParser.cxx \
            Style.cxx
            

HEADERS  += const.hxx \
            qsketch.h \
            Entry.hxx \
            EntryXmlParser.hxx \
            Environment.hxx \
            IqHtml.hxx \
            Note.hxx \
            NoteHtmlWriter.hxx \
            NoteXmlParser.hxx \
            Property.hxx \
            PropertyValue.hxx \
            PropertyXmlParser.hxx \
            Style.hxx

QMAKE_RPATH =

QMAKE_ABSOLUTE_SOURCE_PATH = yes

TARGET      = iqhtml



!win32 {
   LIBS += -lcurses
}
win32 {
   RC_FILE = IqHtml.rc
   HOST_OBJDIR = winobjs
}

####################################
#  Other platform dependent stuff
####################################
DESTDIR      = $$HOST_OBJDIR
OBJECTS_DIR  = $$HOST_OBJDIR
MOC_DIR      = $$HOST_OBJDIR

