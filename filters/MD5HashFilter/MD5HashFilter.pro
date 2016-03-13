#-------------------------------------------------
#
# Project created by QtCreator 2016-01-12T17:14:38
#
#-------------------------------------------------

QT       += gui

CONFIG(debug, debug|release) {
    TARGET = md5hashfilterd
} else {
    TARGET = md5hashfilter
}

TEMPLATE = lib

DESTDIR = ..\\..\\plugins
MOC_DIR = ..\\..\\moc
OBJECTS_DIR = ..\\..\\obj

QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
QMAKE_CLEAN *= $$MOC_DIR\\*$$TARGET*
QMAKE_CLEAN *= $$OBJECTS_DIR\\*$$TARGET*

DEFINES += MD5HASHFILTER_LIBRARY

HEADERS += \
    md5hashfilter.h \
    md5hashfilter_global.h \
    ifilter.h

SOURCES += \
    md5hashfilter.cpp
