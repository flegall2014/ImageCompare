#ifndef SEARCHQMLTAB_H
#define SEARCHQMLTAB_H
#include "qmltab.h"
class QMLSearchModel;

class SearchQMLTab : public QMLTab
{
    Q_OBJECT

public:
    // Constructor:
    SearchQMLTab(QWidget *parent = 0);

    // Destructor:
    virtual ~SearchQMLTab();

    // Set target string:
    void setTargetString(const QString &targetString);
};

#endif // SEARCHQMLTAB_H
