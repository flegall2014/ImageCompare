#include "pictohunterdialog.h"
#include "ui_pictohunterdialog.h"
#include <QFileDialog>

// Constructor:
PictoHunterDialog::PictoHunterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictoHunterDialog),
    mExclusionDirModel(0)
{
    ui->setupUi(this);
    mExclusionDirModel = new QStringListModel(this);
    ui->exclusionListView->setModel(mExclusionDirModel);
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->runButton, SIGNAL(clicked()), SLOT(onRunClicked()));
    connect(ui->selectPictoDirButton, SIGNAL(clicked()), SLOT(onSelectPictoDir()));
    connect(ui->selectSrcCodeDirButton, SIGNAL(clicked()), SLOT(onSelectSrcDir()));
    connect(ui->addExclusionDirectory, SIGNAL(clicked()), SLOT(onAddExclusionDir()));
    connect(ui->cleanPictoDirectoryButton, SIGNAL(clicked()), SLOT(onCleanPictoDirectory()));
}

// Destructor:
PictoHunterDialog::~PictoHunterDialog()
{
    delete ui;
}

// Return picto dir:
const QDir &PictoHunterDialog::pictoDir() const
{
    return mPictoDir;
}

// Return src code dir:
const QDir &PictoHunterDialog::srcCodeDir() const
{
    return mSrcCodeDir;
}

// Select dir1:
void PictoHunterDialog::onSelectPictoDir()
{
    // Get picto dir:
    mPictoDir = QFileDialog::getExistingDirectory(this,  tr("Select Picto Directory"));
    ui->pictoDirTextEdit->setText(mPictoDir.absolutePath());
}

// Select dir1:
void PictoHunterDialog::onSelectSrcDir()
{
    // Get src dir:
    mSrcCodeDir = QFileDialog::getExistingDirectory(this,  tr("Select Src Directory"));
    ui->srcCodeDirTextEdit->setText(mSrcCodeDir.absolutePath());
}

// Add exclusion dir:
void PictoHunterDialog::onAddExclusionDir()
{
    // Get src dir:
    QString exclusionDir = QFileDialog::getExistingDirectory(this,  tr("Select Exclusion Directory"));
    QStringList currentDirs = mExclusionDirModel->stringList();
     if (!currentDirs.contains(exclusionDir, Qt::CaseInsensitive))
        currentDirs << exclusionDir;
    mExclusionDirModel->setStringList(currentDirs);
}

// Clean picto directory:
void PictoHunterDialog::onCleanPictoDirectory()
{
    emit cleanPictoDirectory();
    accept();
}

// Run clicked:
void PictoHunterDialog::onRunClicked()
{
    emit runClicked();
    //accept();
}

// Return selected file extensions:
QStringList PictoHunterDialog::fileExtensions() const
{
    QStringList extensions;
    if (ui->qmlCheckBox->isChecked())
        extensions << "*.qml";
    if (ui->cppCheckBox->isChecked())
        extensions << "*.cpp";
    if (ui->hCheckBox->isChecked())
        extensions << "*.h";
    if (ui->jsCheckBox->isChecked())
        extensions << "*.js";
    return extensions;
}

// Return exclusion directories list:
QStringList PictoHunterDialog::exclusionDirectories() const
{
    return mExclusionDirModel->stringList();
}
