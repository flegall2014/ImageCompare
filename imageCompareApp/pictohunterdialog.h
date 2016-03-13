#ifndef PICTOHUNTERDIALOG_H
#define PICTOHUNTERDIALOG_H
#include <QDialog>
#include <QDir>
#include <QStringListModel>

namespace Ui {
class PictoHunterDialog;
}

class PictoHunterDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor:
    explicit PictoHunterDialog(QWidget *parent = 0);

    // Destructor:
    virtual ~PictoHunterDialog();

    // Return picto dir:
    const QDir &pictoDir() const;

    // Retur src code dir:
    const QDir &srcCodeDir() const;

    // Return selected file extensions:
    QStringList fileExtensions() const;

    // Return exclusion directories:
    QStringList exclusionDirectories() const;

private:
    // UI:
    Ui::PictoHunterDialog *ui;

    // Picto dir:
    QDir mPictoDir;

    // Src code dir:
    QDir mSrcCodeDir;

    // Exclusion directories:
    QStringListModel *mExclusionDirModel;

public slots:
    // Select picto dir:
    void onSelectPictoDir();

    // Select src dir:
    void onSelectSrcDir();

    // Add exclusion dir:
    void onAddExclusionDir();

    // Clean picto directory:
    void onCleanPictoDirectory();

    // Run clicked:
    void onRunClicked();

signals:
    // Run clicked:
    void runClicked();

    // Clean picto directory:
    void cleanPictoDirectory();
};

#endif // PICTOHUNTERDIALOG_H
