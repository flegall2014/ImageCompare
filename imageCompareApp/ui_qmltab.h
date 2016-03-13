/********************************************************************************
** Form generated from reading UI file 'qmltab.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMLTAB_H
#define UI_QMLTAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>
#include "QQuickWidget"

QT_BEGIN_NAMESPACE

class Ui_QMLTab
{
public:
    QGridLayout *gridLayout;
    QQuickWidget *qmlView;

    void setupUi(QWidget *QMLTab)
    {
        if (QMLTab->objectName().isEmpty())
            QMLTab->setObjectName(QStringLiteral("QMLTab"));
        QMLTab->resize(400, 300);
        gridLayout = new QGridLayout(QMLTab);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        qmlView = new QQuickWidget(QMLTab);
        qmlView->setObjectName(QStringLiteral("qmlView"));
        qmlView->setResizeMode(QQuickWidget::SizeRootObjectToView);

        gridLayout->addWidget(qmlView, 0, 0, 1, 1);


        retranslateUi(QMLTab);

        QMetaObject::connectSlotsByName(QMLTab);
    } // setupUi

    void retranslateUi(QWidget *QMLTab)
    {
        QMLTab->setWindowTitle(QApplication::translate("QMLTab", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class QMLTab: public Ui_QMLTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMLTAB_H
