#-------------------------------------------------
#
# Project created by QtCreator 2015-11-13T11:04:41
#
#-------------------------------------------------

QT       += gui script

CONFIG(debug, debug|release) {
    TARGET = stringhunterd
} else {
    TARGET = stringhunter
}
INCLUDEPATH += $$PWD/../imagecompare

TEMPLATE = lib

DESTDIR = ..\\bin
MOC_DIR = ..\\moc
OBJECTS_DIR = ..\\obj

QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
QMAKE_CLEAN *= $$MOC_DIR\\*$$TARGET*
QMAKE_CLEAN *= $$OBJECTS_DIR\\*$$TARGET*

HEADERS += \
    stringhunter.h \
    helper.h

SOURCES += \
    stringhunter.cpp \
    helper.cpp

