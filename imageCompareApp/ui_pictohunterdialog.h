/********************************************************************************
** Form generated from reading UI file 'pictohunterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTOHUNTERDIALOG_H
#define UI_PICTOHUNTERDIALOG_H

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
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PictoHunterDialog
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QCheckBox *hCheckBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QLineEdit *srcCodeDirTextEdit;
    QPushButton *selectSrcCodeDirButton;
    QCheckBox *cppCheckBox;
    QSpacerItem *verticalSpacer_2;
    QCheckBox *jsCheckBox;
    QLabel *label_4;
    QPushButton *addExclusionDirectory;
    QCheckBox *qmlCheckBox;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *pictoDirTextEdit;
    QPushButton *selectPictoDirButton;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *runButton;
    QPushButton *cancelButton;
    QLabel *label;
    QListView *exclusionListView;
    QPushButton *cleanPictoDirectoryButton;

    void setupUi(QDialog *PictoHunterDialog)
    {
        if (PictoHunterDialog->objectName().isEmpty())
            PictoHunterDialog->setObjectName(QStringLiteral("PictoHunterDialog"));
        PictoHunterDialog->resize(650, 541);
        QIcon icon;
        icon.addFile(QStringLiteral(":/qml/icons/ico-application.ico"), QSize(), QIcon::Normal, QIcon::Off);
        PictoHunterDialog->setWindowIcon(icon);
        gridLayout = new QGridLayout(PictoHunterDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);

        hCheckBox = new QCheckBox(PictoHunterDialog);
        hCheckBox->setObjectName(QStringLiteral("hCheckBox"));

        gridLayout->addWidget(hCheckBox, 7, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(PictoHunterDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        horizontalLayout_4->addWidget(label_2);

        srcCodeDirTextEdit = new QLineEdit(PictoHunterDialog);
        srcCodeDirTextEdit->setObjectName(QStringLiteral("srcCodeDirTextEdit"));

        horizontalLayout_4->addWidget(srcCodeDirTextEdit);

        selectSrcCodeDirButton = new QPushButton(PictoHunterDialog);
        selectSrcCodeDirButton->setObjectName(QStringLiteral("selectSrcCodeDirButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/qml/icons/ico-bluefolder.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectSrcCodeDirButton->setIcon(icon1);

        horizontalLayout_4->addWidget(selectSrcCodeDirButton);


        verticalLayout->addLayout(horizontalLayout_4);


        gridLayout->addLayout(verticalLayout, 2, 0, 1, 1);

        cppCheckBox = new QCheckBox(PictoHunterDialog);
        cppCheckBox->setObjectName(QStringLiteral("cppCheckBox"));

        gridLayout->addWidget(cppCheckBox, 6, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 0, 1, 1);

        jsCheckBox = new QCheckBox(PictoHunterDialog);
        jsCheckBox->setObjectName(QStringLiteral("jsCheckBox"));

        gridLayout->addWidget(jsCheckBox, 8, 0, 1, 1);

        label_4 = new QLabel(PictoHunterDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font);

        gridLayout->addWidget(label_4, 11, 0, 1, 1);

        addExclusionDirectory = new QPushButton(PictoHunterDialog);
        addExclusionDirectory->setObjectName(QStringLiteral("addExclusionDirectory"));

        gridLayout->addWidget(addExclusionDirectory, 15, 0, 1, 1);

        qmlCheckBox = new QCheckBox(PictoHunterDialog);
        qmlCheckBox->setObjectName(QStringLiteral("qmlCheckBox"));

        gridLayout->addWidget(qmlCheckBox, 5, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(PictoHunterDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font);

        horizontalLayout_5->addWidget(label_3);

        pictoDirTextEdit = new QLineEdit(PictoHunterDialog);
        pictoDirTextEdit->setObjectName(QStringLiteral("pictoDirTextEdit"));

        horizontalLayout_5->addWidget(pictoDirTextEdit);

        selectPictoDirButton = new QPushButton(PictoHunterDialog);
        selectPictoDirButton->setObjectName(QStringLiteral("selectPictoDirButton"));
        selectPictoDirButton->setIcon(icon1);

        horizontalLayout_5->addWidget(selectPictoDirButton);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        runButton = new QPushButton(PictoHunterDialog);
        runButton->setObjectName(QStringLiteral("runButton"));

        horizontalLayout->addWidget(runButton);

        cancelButton = new QPushButton(PictoHunterDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);


        gridLayout->addLayout(horizontalLayout, 17, 0, 1, 1);

        label = new QLabel(PictoHunterDialog);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        exclusionListView = new QListView(PictoHunterDialog);
        exclusionListView->setObjectName(QStringLiteral("exclusionListView"));

        gridLayout->addWidget(exclusionListView, 14, 0, 1, 1);

        cleanPictoDirectoryButton = new QPushButton(PictoHunterDialog);
        cleanPictoDirectoryButton->setObjectName(QStringLiteral("cleanPictoDirectoryButton"));
        cleanPictoDirectoryButton->setEnabled(true);

        gridLayout->addWidget(cleanPictoDirectoryButton, 16, 0, 1, 1);

        QWidget::setTabOrder(srcCodeDirTextEdit, pictoDirTextEdit);
        QWidget::setTabOrder(pictoDirTextEdit, selectSrcCodeDirButton);
        QWidget::setTabOrder(selectSrcCodeDirButton, selectPictoDirButton);
        QWidget::setTabOrder(selectPictoDirButton, runButton);
        QWidget::setTabOrder(runButton, cancelButton);

        retranslateUi(PictoHunterDialog);

        QMetaObject::connectSlotsByName(PictoHunterDialog);
    } // setupUi

    void retranslateUi(QDialog *PictoHunterDialog)
    {
        PictoHunterDialog->setWindowTitle(QApplication::translate("PictoHunterDialog", "Directory Comparison", 0));
        hCheckBox->setText(QApplication::translate("PictoHunterDialog", "*.h", 0));
        label_2->setText(QApplication::translate("PictoHunterDialog", "Src Code Dir", 0));
        selectSrcCodeDirButton->setText(QString());
        cppCheckBox->setText(QApplication::translate("PictoHunterDialog", "*.cpp", 0));
        jsCheckBox->setText(QApplication::translate("PictoHunterDialog", "*.js", 0));
        label_4->setText(QApplication::translate("PictoHunterDialog", "Exclusion List (picto inside listed directories will be considered as used pictos):", 0));
        addExclusionDirectory->setText(QApplication::translate("PictoHunterDialog", "Add Exclusion Directory", 0));
        qmlCheckBox->setText(QApplication::translate("PictoHunterDialog", "*.qml", 0));
        label_3->setText(QApplication::translate("PictoHunterDialog", "Picto Dir:", 0));
        selectPictoDirButton->setText(QString());
        runButton->setText(QApplication::translate("PictoHunterDialog", "Run", 0));
        cancelButton->setText(QApplication::translate("PictoHunterDialog", "Cancel", 0));
        label->setText(QApplication::translate("PictoHunterDialog", "Select Source Code Dir and Picto Dir", 0));
        cleanPictoDirectoryButton->setText(QApplication::translate("PictoHunterDialog", "Clean Picto Directory", 0));
    } // retranslateUi

};

namespace Ui {
    class PictoHunterDialog: public Ui_PictoHunterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTOHUNTERDIALOG_H
