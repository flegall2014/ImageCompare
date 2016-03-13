#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H
#include <QDialog>
#include <QVariantMap>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    // Constructor:
    explicit PreferencesDialog(QWidget *parent = 0);

    // Destructor:
    virtual ~PreferencesDialog();

    // Set preferences:
    void setPreferences(const QVariantMap &preferences);

    // Get preferences:
    const QVariantMap &preferences() const;

private:
    // Update UI:
    void updateUI();

private:
    Ui::PreferencesDialog *ui;

    // Dialog data:
    QVariantMap mPreferences;

public slots:
    // Apply clicked:
    void onApplyClicked();

    // Select QML dir:
    void onSelectQMLDir();
};

#endif // PREFERENCESDIALOG_H
