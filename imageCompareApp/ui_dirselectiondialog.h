/********************************************************************************
** Form generated from reading UI file 'dirselectiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIRSELECTIONDIALOG_H
#define UI_DIRSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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

class Ui_DirSelectionDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *dir1TextEdit;
    QPushButton *selectDir1Button;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *runButton;
    QPushButton *cancelButton;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *dir2TextEdit;
    QPushButton *selectDir2Button;
    QLabel *label;
    QCheckBox *ambiance1OnlyCheckBox;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *dir3TextEdit;
    QPushButton *selectDir3Button;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_5;
    QLineEdit *dir4TextEdit;
    QPushButton *selectDir4Button;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_6;
    QLineEdit *dir5TextEdit;
    QPushButton *selectDir5Button;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_7;
    QLineEdit *dir6TextEdit;
    QPushButton *selectDir6Button;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DirSelectionDialog)
    {
        if (DirSelectionDialog->objectName().isEmpty())
            DirSelectionDialog->setObjectName(QStringLiteral("DirSelectionDialog"));
        DirSelectionDialog->setEnabled(true);
        DirSelectionDialog->resize(650, 395);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        DirSelectionDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(DirSelectionDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(DirSelectionDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        dir1TextEdit = new QLineEdit(DirSelectionDialog);
        dir1TextEdit->setObjectName(QStringLiteral("dir1TextEdit"));
        dir1TextEdit->setEnabled(true);

        horizontalLayout_4->addWidget(dir1TextEdit);

        selectDir1Button = new QPushButton(DirSelectionDialog);
        selectDir1Button->setObjectName(QStringLiteral("selectDir1Button"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qml/icons/ico-bluefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectDir1Button->setIcon(icon1);

        horizontalLayout_4->addWidget(selectDir1Button);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        runButton = new QPushButton(DirSelectionDialog);
        runButton->setObjectName(QStringLiteral("runButton"));

        horizontalLayout->addWidget(runButton);

        cancelButton = new QPushButton(DirSelectionDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 9, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(DirSelectionDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_5->addWidget(label_3);

        dir2TextEdit = new QLineEdit(DirSelectionDialog);
        dir2TextEdit->setObjectName(QStringLiteral("dir2TextEdit"));
        dir2TextEdit->setEnabled(true);

        horizontalLayout_5->addWidget(dir2TextEdit);

        selectDir2Button = new QPushButton(DirSelectionDialog);
        selectDir2Button->setObjectName(QStringLiteral("selectDir2Button"));
        selectDir2Button->setIcon(icon1);

        horizontalLayout_5->addWidget(selectDir2Button);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        label = new QLabel(DirSelectionDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        ambiance1OnlyCheckBox = new QCheckBox(DirSelectionDialog);
        ambiance1OnlyCheckBox->setObjectName(QStringLiteral("ambiance1OnlyCheckBox"));

        gridLayout->addWidget(ambiance1OnlyCheckBox, 8, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(DirSelectionDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        horizontalLayout_6->addWidget(label_4);

        dir3TextEdit = new QLineEdit(DirSelectionDialog);
        dir3TextEdit->setObjectName(QStringLiteral("dir3TextEdit"));
        dir3TextEdit->setEnabled(true);

        horizontalLayout_6->addWidget(dir3TextEdit);

        selectDir3Button = new QPushButton(DirSelectionDialog);
        selectDir3Button->setObjectName(QStringLiteral("selectDir3Button"));
        selectDir3Button->setIcon(icon1);

        horizontalLayout_6->addWidget(selectDir3Button);


        gridLayout->addLayout(horizontalLayout_6, 4, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_5 = new QLabel(DirSelectionDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        horizontalLayout_7->addWidget(label_5);

        dir4TextEdit = new QLineEdit(DirSelectionDialog);
        dir4TextEdit->setObjectName(QStringLiteral("dir4TextEdit"));
        dir4TextEdit->setEnabled(true);

        horizontalLayout_7->addWidget(dir4TextEdit);

        selectDir4Button = new QPushButton(DirSelectionDialog);
        selectDir4Button->setObjectName(QStringLiteral("selectDir4Button"));
        selectDir4Button->setIcon(icon1);

        horizontalLayout_7->addWidget(selectDir4Button);


        gridLayout->addLayout(horizontalLayout_7, 5, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_6 = new QLabel(DirSelectionDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        horizontalLayout_8->addWidget(label_6);

        dir5TextEdit = new QLineEdit(DirSelectionDialog);
        dir5TextEdit->setObjectName(QStringLiteral("dir5TextEdit"));
        dir5TextEdit->setEnabled(true);

        horizontalLayout_8->addWidget(dir5TextEdit);

        selectDir5Button = new QPushButton(DirSelectionDialog);
        selectDir5Button->setObjectName(QStringLiteral("selectDir5Button"));
        selectDir5Button->setIcon(icon1);

        horizontalLayout_8->addWidget(selectDir5Button);


        gridLayout->addLayout(horizontalLayout_8, 6, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_7 = new QLabel(DirSelectionDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        horizontalLayout_9->addWidget(label_7);

        dir6TextEdit = new QLineEdit(DirSelectionDialog);
        dir6TextEdit->setObjectName(QStringLiteral("dir6TextEdit"));
        dir6TextEdit->setEnabled(true);

        horizontalLayout_9->addWidget(dir6TextEdit);

        selectDir6Button = new QPushButton(DirSelectionDialog);
        selectDir6Button->setObjectName(QStringLiteral("selectDir6Button"));
        selectDir6Button->setIcon(icon1);

        horizontalLayout_9->addWidget(selectDir6Button);


        gridLayout->addLayout(horizontalLayout_9, 7, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 8, 0, 1, 1);

        QWidget::setTabOrder(dir1TextEdit, dir2TextEdit);
        QWidget::setTabOrder(dir2TextEdit, selectDir1Button);
        QWidget::setTabOrder(selectDir1Button, selectDir2Button);
        QWidget::setTabOrder(selectDir2Button, runButton);
        QWidget::setTabOrder(runButton, cancelButton);

        retranslateUi(DirSelectionDialog);

        QMetaObject::connectSlotsByName(DirSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *DirSelectionDialog)
    {
        DirSelectionDialog->setWindowTitle(QApplication::translate("DirSelectionDialog", "Directory Comparison", 0));
        label_2->setText(QApplication::translate("DirSelectionDialog", "Dir1:", 0));
        selectDir1Button->setText(QString());
        runButton->setText(QApplication::translate("DirSelectionDialog", "Run", 0));
        cancelButton->setText(QApplication::translate("DirSelectionDialog", "Cancel", 0));
        label_3->setText(QApplication::translate("DirSelectionDialog", "Dir2:", 0));
        selectDir2Button->setText(QString());
        label->setText(QApplication::translate("DirSelectionDialog", "Select Target Directories", 0));
        ambiance1OnlyCheckBox->setText(QApplication::translate("DirSelectionDialog", "Ambiance 1 Only", 0));
        label_4->setText(QApplication::translate("DirSelectionDialog", "Dir3:", 0));
        selectDir3Button->setText(QString());
        label_5->setText(QApplication::translate("DirSelectionDialog", "Dir4:", 0));
        selectDir4Button->setText(QString());
        label_6->setText(QApplication::translate("DirSelectionDialog", "Dir5:", 0));
        selectDir5Button->setText(QString());
        label_7->setText(QApplication::translate("DirSelectionDialog", "Dir6:", 0));
        selectDir6Button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DirSelectionDialog: public Ui_DirSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIRSELECTIONDIALOG_H
