/********************************************************************************
** Form generated from reading UI file 'globalstatisticstab.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOBALSTATISTICSTAB_H
#define UI_GLOBALSTATISTICSTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>
#include "QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_GlobalStatisticsTab
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QTreeView *treeView;
    QQuickWidget *qmlView;

    void setupUi(QWidget *GlobalStatisticsTab)
    {
        if (GlobalStatisticsTab->objectName().isEmpty())
            GlobalStatisticsTab->setObjectName(QStringLiteral("GlobalStatisticsTab"));
        GlobalStatisticsTab->resize(400, 300);
        gridLayout = new QGridLayout(GlobalStatisticsTab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        treeView = new QTreeView(GlobalStatisticsTab);
        treeView->setObjectName(QStringLiteral("treeView"));

        horizontalLayout->addWidget(treeView);

        qmlView = new QQuickWidget(GlobalStatisticsTab);
        qmlView->setObjectName(QStringLiteral("qmlView"));
        qmlView->setResizeMode(QQuickWidget::SizeRootObjectToView);

        horizontalLayout->addWidget(qmlView);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(GlobalStatisticsTab);

        QMetaObject::connectSlotsByName(GlobalStatisticsTab);
    } // setupUi

    void retranslateUi(QWidget *GlobalStatisticsTab)
    {
        GlobalStatisticsTab->setWindowTitle(QApplication::translate("GlobalStatisticsTab", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class GlobalStatisticsTab: public Ui_GlobalStatisticsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOBALSTATISTICSTAB_H
