#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QFileDialog>

// Constructor:
PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui->applyButton, SIGNAL(clicked()), SLOT(onApplyClicked()));
    connect(ui->selectQMLDirbutton, SIGNAL(clicked()), SLOT(onSelectQMLDir()));
}

// Destructor:
PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

// Apply clicked:
void PreferencesDialog::onApplyClicked()
{
    mPreferences["QML_DIR"] = ui->qmlDirEdit->text();
    accept();
}

// Select QML dir:
void PreferencesDialog::onSelectQMLDir()
{
    ui->qmlDirEdit->setText(QFileDialog::getExistingDirectory(this,  tr("Select Target QML Directory")));
}

// Set preferences:
void PreferencesDialog::setPreferences(const QVariantMap &preferences)
{
    mPreferences = preferences;
    updateUI();
}

// Return preferences:
const QVariantMap &PreferencesDialog::preferences() const
{
    return mPreferences;
}

// Update UI:
void PreferencesDialog::updateUI()
{
    ui->qmlDirEdit->setText(mPreferences["QML_DIR"].toString());
}
