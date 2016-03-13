/********************************************************************************
** Form generated from reading UI file 'preferencesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFERENCESDIALOG_H
#define UI_PREFERENCESDIALOG_H

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

class Ui_PreferencesDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *qmlDirEdit;
    QPushButton *selectQMLDirbutton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QPushButton *cancelButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *label;
    QLabel *label_4;

    void setupUi(QDialog *PreferencesDialog)
    {
        if (PreferencesDialog->objectName().isEmpty())
            PreferencesDialog->setObjectName(QStringLiteral("PreferencesDialog"));
        PreferencesDialog->resize(650, 300);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        PreferencesDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(PreferencesDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        qmlDirEdit = new QLineEdit(PreferencesDialog);
        qmlDirEdit->setObjectName(QStringLiteral("qmlDirEdit"));

        horizontalLayout_4->addWidget(qmlDirEdit);

        selectQMLDirbutton = new QPushButton(PreferencesDialog);
        selectQMLDirbutton->setObjectName(QStringLiteral("selectQMLDirbutton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qml/icons/ico-bluefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectQMLDirbutton->setIcon(icon1);

        horizontalLayout_4->addWidget(selectQMLDirbutton);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        applyButton = new QPushButton(PreferencesDialog);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout->addWidget(applyButton);

        cancelButton = new QPushButton(PreferencesDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 5, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        label = new QLabel(PreferencesDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(PreferencesDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label_4->setFont(font1);

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        QWidget::setTabOrder(selectQMLDirbutton, applyButton);
        QWidget::setTabOrder(applyButton, cancelButton);

        retranslateUi(PreferencesDialog);

        QMetaObject::connectSlotsByName(PreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *PreferencesDialog)
    {
        PreferencesDialog->setWindowTitle(QApplication::translate("PreferencesDialog", "Preferences", 0));
        selectQMLDirbutton->setText(QString());
        applyButton->setText(QApplication::translate("PreferencesDialog", "Apply", 0));
        cancelButton->setText(QApplication::translate("PreferencesDialog", "Cancel", 0));
        label->setText(QApplication::translate("PreferencesDialog", "Preferences", 0));
        label_4->setText(QApplication::translate("PreferencesDialog", "QML Search Directory:", 0));
    } // retranslateUi

};

namespace Ui {
    class PreferencesDialog: public Ui_PreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFERENCESDIALOG_H
