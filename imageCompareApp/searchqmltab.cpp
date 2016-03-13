#include "searchqmltab.h"
#include "qmlsearchmodel.h"

// Constructor:
SearchQMLTab::SearchQMLTab(QWidget *parent) : QMLTab(parent)
{
}

// Destructor:
SearchQMLTab::~SearchQMLTab()
{
}

// Set target string:
void SearchQMLTab::setTargetString(const QString &targetString)
{
    setContextProperty("_targetString", targetString);
}
