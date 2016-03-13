/********************************************************************************
** Form generated from reading UI file 'qmlsearchdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QMLSEARCHDIALOG_H
#define UI_QMLSEARCHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_QMLSearchDialog
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *runButton;
    QPushButton *cancelButton;
    QVBoxLayout *verticalLayout;
    QLineEdit *searchString;
    QListView *listView;
    QTextEdit *textBrowser;

    void setupUi(QDialog *QMLSearchDialog)
    {
        if (QMLSearchDialog->objectName().isEmpty())
            QMLSearchDialog->setObjectName(QStringLiteral("QMLSearchDialog"));
        QMLSearchDialog->resize(1024, 512);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        QMLSearchDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(QMLSearchDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        runButton = new QPushButton(QMLSearchDialog);
        runButton->setObjectName(QStringLiteral("runButton"));

        horizontalLayout->addWidget(runButton);

        cancelButton = new QPushButton(QMLSearchDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        searchString = new QLineEdit(QMLSearchDialog);
        searchString->setObjectName(QStringLiteral("searchString"));

        verticalLayout->addWidget(searchString);

        listView = new QListView(QMLSearchDialog);
        listView->setObjectName(QStringLiteral("listView"));

        verticalLayout->addWidget(listView);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        textBrowser = new QTextEdit(QMLSearchDialog);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 1, 1, 1);

        QWidget::setTabOrder(runButton, cancelButton);

        retranslateUi(QMLSearchDialog);

        QMetaObject::connectSlotsByName(QMLSearchDialog);
    } // setupUi

    void retranslateUi(QDialog *QMLSearchDialog)
    {
        QMLSearchDialog->setWindowTitle(QApplication::translate("QMLSearchDialog", "Search target string in QML files", 0));
        runButton->setText(QApplication::translate("QMLSearchDialog", "Run", 0));
        cancelButton->setText(QApplication::translate("QMLSearchDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class QMLSearchDialog: public Ui_QMLSearchDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QMLSEARCHDIALOG_H
