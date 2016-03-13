#-------------------------------------------------
#
# Project created by QtCreator 2016-01-18T09:04:28
#
#-------------------------------------------------

QT       += core gui qml quick quickwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = imageCompare
TEMPLATE = app

INCLUDEPATH += $$PWD/../stringhunter
DEPENDPATH += $$PWD/../stringhunter
INCLUDEPATH += $$PWD/../filters

DESTDIR = ..\\bin
MOC_DIR = ..\\moc
OBJECTS_DIR = ..\\obj

QMAKE_CLEAN *= $$DESTDIR\\*$$TARGET*
QMAKE_CLEAN *= $$MOC_DIR\\*$$TARGET*
QMAKE_CLEAN *= $$OBJECTS_DIR\\*$$TARGET*

CONFIG(debug, debug|release) {
    LIBS += -L$$PWD/../bin/ -lstringhunterd
    TARGET = imageCompared
} else {
    LIBS += -L$$PWD/../bin/ -lstringhunter
    TARGET = imageCompare
}

FORMS += \
    mainwindow.ui \
    dirselectiondialog.ui \
    ambianceselectiondialog.ui \
    qmlsearchdialog.ui \
    qmltab.ui \
    preferencesdialog.ui \
    pictohunterdialog.ui

HEADERS += \
    node.h \
    treemodel.h \
    utils.h \
    ifilter.h \
    imagemodel.h \
    controller.h \
    treemodelfilter.h \
    mainwindow.h \
    imagemodelfilter.h \
    iservice.h \
    imagecompare.h \
    statusworker.h \
    defs.h \
    dirselectiondialog.h \
    ambianceselectiondialog.h \
    spacer.h \
    qmlsearchmodel.h \
    texteditor.h \
    textedit.h \
    qmltab.h \
    preferencesdialog.h \
    searchqmltab.h \
    statisticstab.h \
    problemmodelfilter.h \
    filtermgr.h \
    preferencemgr.h \
    reportmgr.h \
    pictohunter.h \
    pictohunterdialog.h \
    pictocoverageservice.h

SOURCES += \
    main.cpp \
    node.cpp \
    treemodel.cpp \
    utils.cpp \
    imagemodel.cpp \
    controller.cpp \
    treemodelfilter.cpp \
    mainwindow.cpp \
    imagemodelfilter.cpp \
    imagecompare.cpp \
    statusworker.cpp \
    dirselectiondialog.cpp \
    ambianceselectiondialog.cpp \
    spacer.cpp \
    qmlsearchmodel.cpp \
    texteditor.cpp \
    textedit.cpp \
    qmltab.cpp \
    preferencesdialog.cpp \
    searchqmltab.cpp \
    statisticstab.cpp \
    problemmodelfilter.cpp \
    filtermgr.cpp \
    preferencemgr.cpp \
    reportmgr.cpp \
    pictohunter.cpp \
    pictohunterdialog.cpp \
    pictocoverageservice.cpp

DISTFILES +=

RESOURCES += \
    resources.qrc


