#-------------------------------------------------
#
# Project created by QtCreator 2016-01-12T17:14:38
#
#-------------------------------------------------

QT       += gui

CONFIG(debug, debug|release) {
    TARGET = corruptedfilefilterd
} else {
    TARGET = corruptedfile
}

TEMPLATE = lib

DESTDIR = ..\\..\\plugins
MOC_DIR = ..\\..\\moc
OBJECTS_DIR = ..\\..\\obj

QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
QMAKE_CLEAN *= $$MOC_DIR\\*$$TARGET*
QMAKE_CLEAN *= $$OBJECTS_DIR\\*$$TARGET*

DEFINES += CORRUPTEDFILEFILTER_LIBRARY

HEADERS += \
    corruptedfilefilter.h \
    corruptedfilefilter_global.h \
    ifilter.h

SOURCES += \
    corruptedfilefilter.cpp
