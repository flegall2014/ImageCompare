/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "QtQuickWidgets/QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *selectDir1Action;
    QAction *exitAction;
    QAction *selectDir2Action;
    QAction *directoryCompareAction;
    QAction *ambianceCompareAction;
    QAction *preferencesAction;
    QAction *batchProcessingAction;
    QAction *browseSingleDirectoryAction;
    QAction *openReportAction;
    QAction *pictoCoverageAction;
    QAction *fileStatsAction;
    QAction *closeAllAction;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTreeView *treeView;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *processingTab;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QQuickWidget *processingQmlView;
    QWidget *quickStatsTab;
    QGridLayout *gridLayout_3;
    QQuickWidget *quickStatsQmlView;
    QWidget *problemsTab;
    QGridLayout *gridLayout_4;
    QQuickWidget *problemQmlView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QMenu *menuWindows;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        selectDir1Action = new QAction(MainWindow);
        selectDir1Action->setObjectName(QStringLiteral("selectDir1Action"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qml/icons/ico-greenfolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectDir1Action->setIcon(icon1);
        selectDir1Action->setShortcutContext(Qt::ApplicationShortcut);
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/qml/icons/ico-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitAction->setIcon(icon2);
        exitAction->setShortcutContext(Qt::ApplicationShortcut);
        selectDir2Action = new QAction(MainWindow);
        selectDir2Action->setObjectName(QStringLiteral("selectDir2Action"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/qml/icons/ico-bluefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectDir2Action->setIcon(icon3);
        directoryCompareAction = new QAction(MainWindow);
        directoryCompareAction->setObjectName(QStringLiteral("directoryCompareAction"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/qml/icons/ico-directorycompare.png"), QSize(), QIcon::Normal, QIcon::Off);
        directoryCompareAction->setIcon(icon4);
        ambianceCompareAction = new QAction(MainWindow);
        ambianceCompareAction->setObjectName(QStringLiteral("ambianceCompareAction"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/qml/icons/ico-ambiancecompare.png"), QSize(), QIcon::Normal, QIcon::Off);
        ambianceCompareAction->setIcon(icon5);
        preferencesAction = new QAction(MainWindow);
        preferencesAction->setObjectName(QStringLiteral("preferencesAction"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/qml/icons/ico-preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        preferencesAction->setIcon(icon6);
        batchProcessingAction = new QAction(MainWindow);
        batchProcessingAction->setObjectName(QStringLiteral("batchProcessingAction"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/qml/icons/ico-batch.png"), QSize(), QIcon::Normal, QIcon::Off);
        batchProcessingAction->setIcon(icon7);
        browseSingleDirectoryAction = new QAction(MainWindow);
        browseSingleDirectoryAction->setObjectName(QStringLiteral("browseSingleDirectoryAction"));
        browseSingleDirectoryAction->setIcon(icon3);
        openReportAction = new QAction(MainWindow);
        openReportAction->setObjectName(QStringLiteral("openReportAction"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/qml/icons/ico-report.png"), QSize(), QIcon::Normal, QIcon::Off);
        openReportAction->setIcon(icon8);
        pictoCoverageAction = new QAction(MainWindow);
        pictoCoverageAction->setObjectName(QStringLiteral("pictoCoverageAction"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/qml/icons/ico-picto-coverage.png"), QSize(), QIcon::Normal, QIcon::Off);
        pictoCoverageAction->setIcon(icon9);
        fileStatsAction = new QAction(MainWindow);
        fileStatsAction->setObjectName(QStringLiteral("fileStatsAction"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/qml/icons/ico-stats.png"), QSize(), QIcon::Normal, QIcon::Off);
        fileStatsAction->setIcon(icon10);
        closeAllAction = new QAction(MainWindow);
        closeAllAction->setObjectName(QStringLiteral("closeAllAction"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/qml/icons/ico-closeall.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeAllAction->setIcon(icon11);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setMaximumSize(QSize(288, 16777215));

        gridLayout->addWidget(treeView, 1, 0, 1, 1);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setTabsClosable(true);
        processingTab = new QWidget();
        processingTab->setObjectName(QStringLiteral("processingTab"));
        gridLayout_2 = new QGridLayout(processingTab);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        processingQmlView = new QQuickWidget(processingTab);
        processingQmlView->setObjectName(QStringLiteral("processingQmlView"));
        processingQmlView->setResizeMode(QQuickWidget::SizeRootObjectToView);

        horizontalLayout->addWidget(processingQmlView);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        tabWidget->addTab(processingTab, QString());
        quickStatsTab = new QWidget();
        quickStatsTab->setObjectName(QStringLiteral("quickStatsTab"));
        gridLayout_3 = new QGridLayout(quickStatsTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        quickStatsQmlView = new QQuickWidget(quickStatsTab);
        quickStatsQmlView->setObjectName(QStringLiteral("quickStatsQmlView"));
        quickStatsQmlView->setResizeMode(QQuickWidget::SizeRootObjectToView);

        gridLayout_3->addWidget(quickStatsQmlView, 0, 0, 1, 1);

        tabWidget->addTab(quickStatsTab, QString());
        problemsTab = new QWidget();
        problemsTab->setObjectName(QStringLiteral("problemsTab"));
        gridLayout_4 = new QGridLayout(problemsTab);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        problemQmlView = new QQuickWidget(problemsTab);
        problemQmlView->setObjectName(QStringLiteral("problemQmlView"));
        problemQmlView->setResizeMode(QQuickWidget::SizeRootObjectToView);

        gridLayout_4->addWidget(problemQmlView, 0, 0, 1, 1);

        tabWidget->addTab(problemsTab, QString());
        splitter->addWidget(tabWidget);

        gridLayout->addWidget(splitter, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuOptions = new QMenu(menubar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        menuWindows = new QMenu(menubar);
        menuWindows->setObjectName(QStringLiteral("menuWindows"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuWindows->menuAction());
        menubar->addAction(menuOptions->menuAction());
        menuFile->addAction(browseSingleDirectoryAction);
        menuFile->addAction(directoryCompareAction);
        menuFile->addAction(ambianceCompareAction);
        menuFile->addAction(batchProcessingAction);
        menuFile->addAction(pictoCoverageAction);
        menuFile->addAction(openReportAction);
        menuFile->addAction(fileStatsAction);
        menuFile->addAction(exitAction);
        menuOptions->addAction(preferencesAction);
        menuWindows->addAction(closeAllAction);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Ambiance Compare", 0));
        selectDir1Action->setText(QApplication::translate("MainWindow", "Select Dir1", 0));
        exitAction->setText(QApplication::translate("MainWindow", "Exit", 0));
        selectDir2Action->setText(QApplication::translate("MainWindow", "Select Dir2", 0));
        directoryCompareAction->setText(QApplication::translate("MainWindow", "Directory Compare", 0));
        ambianceCompareAction->setText(QApplication::translate("MainWindow", "Ambiance Compare", 0));
        preferencesAction->setText(QApplication::translate("MainWindow", "Preferences", 0));
        batchProcessingAction->setText(QApplication::translate("MainWindow", "Batch Processing", 0));
        browseSingleDirectoryAction->setText(QApplication::translate("MainWindow", "Browse Single Directory", 0));
        openReportAction->setText(QApplication::translate("MainWindow", "Open Report File", 0));
        pictoCoverageAction->setText(QApplication::translate("MainWindow", "Picto Coverage", 0));
        fileStatsAction->setText(QApplication::translate("MainWindow", "File Statistics", 0));
        closeAllAction->setText(QApplication::translate("MainWindow", "Close All", 0));
        tabWidget->setTabText(tabWidget->indexOf(processingTab), QApplication::translate("MainWindow", "Processing", 0));
        tabWidget->setTabText(tabWidget->indexOf(quickStatsTab), QApplication::translate("MainWindow", "Quick Stats", 0));
        tabWidget->setTabText(tabWidget->indexOf(problemsTab), QApplication::translate("MainWindow", "Problems", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
        menuWindows->setTitle(QApplication::translate("MainWindow", "Windows", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
