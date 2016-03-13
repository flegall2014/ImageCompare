#include "dirselectiondialog.h"
#include "ui_dirselectiondialog.h"
#include <QFileDialog>

// Constructor:
DirSelectionDialog::DirSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DirSelectionDialog),
    mAmbiance1Only(false)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->runButton, SIGNAL(clicked()), SLOT(onRunClicked()));
    connect(ui->selectDir1Button, SIGNAL(clicked()), SLOT(onSelectDir1()));
    connect(ui->selectDir2Button, SIGNAL(clicked()), SLOT(onSelectDir2()));
    connect(ui->selectDir3Button, SIGNAL(clicked()), SLOT(onSelectDir3()));
    connect(ui->selectDir4Button, SIGNAL(clicked()), SLOT(onSelectDir4()));
    connect(ui->selectDir5Button, SIGNAL(clicked()), SLOT(onSelectDir5()));
    connect(ui->selectDir6Button, SIGNAL(clicked()), SLOT(onSelectDir6()));
    connect(ui->ambiance1OnlyCheckBox, SIGNAL(clicked(bool)), SLOT(onAmbiance1OnlyClicked(bool)));
}

// Destructor:
DirSelectionDialog::~DirSelectionDialog()
{
    delete ui;
}

// Ambiance 1 only?
bool DirSelectionDialog::ambiance1Only() const
{
    return mAmbiance1Only;
}

// Return list of valid directories:
QList<QDir> DirSelectionDialog::validDirectories(QStringList &dirIds)
{
    QStringList dirLabels;
    dirLabels << ui->dir1TextEdit->text() << ui->dir2TextEdit->text()
        << ui->dir3TextEdit->text() << ui->dir4TextEdit->text()
            << ui->dir5TextEdit->text() << ui->dir6TextEdit->text();
    dirIds.clear();
    QStringList allDirIds;
    allDirIds << "Dir1" << "Dir2" << "Dir3" << "Dir4" << "Dir5" << "Dir6";

    QList<QDir> allDirs;
    for (int i=0; i<dirLabels.size(); i++)
    {
        // Get dir label:
        QString dirLabel = dirLabels[i];
        if (dirLabel.simplified().isEmpty())
            continue;

        // Dir exists?
        QDir dir(dirLabel);
        if (!dir.exists())
            continue;

        // Update:
        allDirs << dir;
        dirIds << allDirIds[i];
    }

    return allDirs;
}

// Select dir1:
void DirSelectionDialog::onSelectDir1()
{
    // Get dir1:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 1"));
    ui->dir1TextEdit->setText(dir.absolutePath());
}

// Select dir2:
void DirSelectionDialog::onSelectDir2()
{
    // Get dir2:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 2"));
    ui->dir2TextEdit->setText(dir.absolutePath());
}

// Select dir3:
void DirSelectionDialog::onSelectDir3()
{
    // Get dir3:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 3"));
    ui->dir3TextEdit->setText(dir.absolutePath());
}

// Select dir4:
void DirSelectionDialog::onSelectDir4()
{
    // Get dir4:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 4"));
    ui->dir4TextEdit->setText(dir.absolutePath());
}

// Select dir5:
void DirSelectionDialog::onSelectDir5()
{
    // Get dir5:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 5"));
    ui->dir5TextEdit->setText(dir.absolutePath());
}

// Select dir6:
void DirSelectionDialog::onSelectDir6()
{
    // Get dir6:
    QDir dir = QFileDialog::getExistingDirectory(this,  tr("Select Directory 6"));
    ui->dir6TextEdit->setText(dir.absolutePath());
}

// Run clicked:
void DirSelectionDialog::onRunClicked()
{
    emit runClicked();
    accept();
}

// Ambiance 1 only clicked:
void DirSelectionDialog::onAmbiance1OnlyClicked(bool checked)
{
    mAmbiance1Only = checked;
}
