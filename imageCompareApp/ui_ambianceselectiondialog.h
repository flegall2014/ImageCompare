/********************************************************************************
** Form generated from reading UI file 'ambianceselectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AMBIANCESELECTIONDIALOG_H
#define UI_AMBIANCESELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AmbianceSelectionDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *rootTextEdit;
    QPushButton *selectImagesDirButton;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *runButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *AmbianceSelectionDialog)
    {
        if (AmbianceSelectionDialog->objectName().isEmpty())
            AmbianceSelectionDialog->setObjectName(QStringLiteral("AmbianceSelectionDialog"));
        AmbianceSelectionDialog->resize(650, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        AmbianceSelectionDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(AmbianceSelectionDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(AmbianceSelectionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        rootTextEdit = new QLineEdit(AmbianceSelectionDialog);
        rootTextEdit->setObjectName(QStringLiteral("rootTextEdit"));

        horizontalLayout_4->addWidget(rootTextEdit);

        selectImagesDirButton = new QPushButton(AmbianceSelectionDialog);
        selectImagesDirButton->setObjectName(QStringLiteral("selectImagesDirButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qml/icons/ico-bluefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectImagesDirButton->setIcon(icon1);

        horizontalLayout_4->addWidget(selectImagesDirButton);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        label = new QLabel(AmbianceSelectionDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        runButton = new QPushButton(AmbianceSelectionDialog);
        runButton->setObjectName(QStringLiteral("runButton"));

        horizontalLayout->addWidget(runButton);

        cancelButton = new QPushButton(AmbianceSelectionDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 4, 0, 1, 1);

        QWidget::setTabOrder(selectImagesDirButton, runButton);
        QWidget::setTabOrder(runButton, cancelButton);

        retranslateUi(AmbianceSelectionDialog);

        QMetaObject::connectSlotsByName(AmbianceSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *AmbianceSelectionDialog)
    {
        AmbianceSelectionDialog->setWindowTitle(QApplication::translate("AmbianceSelectionDialog", "Ambiance Comparison", 0));
        label_2->setText(QApplication::translate("AmbianceSelectionDialog", "Root Dir:", 0));
        selectImagesDirButton->setText(QString());
        label->setText(QApplication::translate("AmbianceSelectionDialog", "Select Root Directory", 0));
        runButton->setText(QApplication::translate("AmbianceSelectionDialog", "Run", 0));
        cancelButton->setText(QApplication::translate("AmbianceSelectionDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class AmbianceSelectionDialog: public Ui_AmbianceSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AMBIANCESELECTIONDIALOG_H
