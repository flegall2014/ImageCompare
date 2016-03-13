#ifndef AMBIANCESELECTIONDIALOG_H
#define AMBIANCESELECTIONDIALOG_H
#include <QDialog>
#include <QDir>

namespace Ui {
class AmbianceSelectionDialog;
}

class AmbianceSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor:
    explicit AmbianceSelectionDialog(QWidget *parent = 0);

    // Destructor:
    virtual ~AmbianceSelectionDialog();

    // Get root dir:
    const QDir &rootDir() const;

private:
    // UI:
    Ui::AmbianceSelectionDialog *ui;

    // Root dir:
    QDir mRootDir;

public slots:
    // Select images dir:
    void onSelectImagesDir();

    // Run clicked:
    void onRunClicked();

signals:
    // Run clicked:
    void runClicked();
};

#endif // AMBIANCESELECTIONDIALOG_H
