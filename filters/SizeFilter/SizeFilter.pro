#-------------------------------------------------
#
# Project created by QtCreator 2016-01-12T17:14:38
#
#-------------------------------------------------

QT       += gui

CONFIG(debug, debug|release) {
    TARGET = sizefilterd
} else {
    TARGET = sizefilter
}

TEMPLATE = lib

DESTDIR = ..\\..\\plugins
MOC_DIR = ..\\..\\moc
OBJECTS_DIR = ..\\..\\obj

QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
QMAKE_CLEAN *= $$MOC_DIR\\*$$TARGET*
QMAKE_CLEAN *= $$OBJECTS_DIR\\*$$TARGET*

DEFINES += SIZEFILTER_LIBRARY

SOURCES += \
    sizefilter.cpp

HEADERS +=\
        ifilter.h \
    sizefilter.h \
    sizefilter_global.h


