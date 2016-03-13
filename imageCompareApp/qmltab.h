#ifndef QMLTAB_H
#define QMLTAB_H
#include <QWidget>
class Controller;
class QMLSearchModel;

namespace Ui {
class QMLTab;
}

class QMLTab : public QWidget
{
    Q_OBJECT

public:
    // Destructor:
    virtual ~QMLTab();

    // Set source:
    void setSource(const QString &source);

    // Set contect property:
    void setContextProperty(const QString &propName, const QVariant &propValue);

    // Set contect property:
    void setContextProperty(const QString &propName, QObject *propValue);

protected:
    // Constructor:
    explicit QMLTab(QWidget *parent = 0);

private:
    // UI:
    Ui::QMLTab *ui;
};

#endif // QMLTAB_H
