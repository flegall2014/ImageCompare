#ifndef DIRSELECTIONDIALOG_H
#define DIRSELECTIONDIALOG_H
#include <QDialog>
#include <QDir>

namespace Ui {
class DirSelectionDialog;
}

class DirSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor:
    explicit DirSelectionDialog(QWidget *parent = 0);

    // Destructor:
    virtual ~DirSelectionDialog();

    // Return valid directories:
    QList<QDir> validDirectories(QStringList &dirIds);

    // Ambiance 1 only?
    bool ambiance1Only() const;

private:
    // UI:
    Ui::DirSelectionDialog *ui;

    // Ambiance 1 only?
    bool mAmbiance1Only;

public slots:
    // Select dir 1:
    void onSelectDir1();

    // Select dir 2:
    void onSelectDir2();

    // Select dir 3:
    void onSelectDir3();

    // Select dir 4:
    void onSelectDir4();

    // Select dir 5:
    void onSelectDir5();

    // Select dir6:
    void onSelectDir6();

    // Run clicked:
    void onRunClicked();

    // Ambiance 1 only clicked:
    void onAmbiance1OnlyClicked(bool);

signals:
    // Run clicked:
    void runClicked();
};

#endif // DIRSELECTIONDIALOG_H
