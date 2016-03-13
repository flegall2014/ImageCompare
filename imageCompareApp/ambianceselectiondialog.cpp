#include "ambianceselectiondialog.h"
#include "ui_ambianceselectiondialog.h"
#include "utils.h"
#include <QFileDialog>
#include <QMessageBox>

// Constructor:
AmbianceSelectionDialog::AmbianceSelectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AmbianceSelectionDialog)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->runButton, SIGNAL(clicked()), SLOT(onRunClicked()));
    connect(ui->selectImagesDirButton, SIGNAL(clicked()), SLOT(onSelectImagesDir()));
}

// Destructor:
AmbianceSelectionDialog::~AmbianceSelectionDialog()
{
    delete ui;
}

// Return root dir:
const QDir &AmbianceSelectionDialog::rootDir() const
{
    return mRootDir;
}

// Select images dir:
void AmbianceSelectionDialog::onSelectImagesDir()
{
    // Get root dir:
    mRootDir = QFileDialog::getExistingDirectory(this,  tr("Select Root Directory"));
    ui->rootTextEdit->setText(mRootDir.absolutePath());
}

// Run clicked:
void AmbianceSelectionDialog::onRunClicked()
{
    // Check universe:
    QList<QDir> ambianceDirList;
    if (!Utils::checkImagesDirectory(mRootDir, ambianceDirList))
    {
        QString errorMsg = mRootDir.absolutePath() + " DOES NOT CONTAIN ANY AMBIANCE";
        QMessageBox::critical(this, tr("Image Compare Error"), errorMsg);
        return;
    }

    emit runClicked();
    accept();
}
