#include "qmltab.h"
#include "ui_qmltab.h"
#include <QQmlEngine>
#include <QQmlContext>
#include "controller.h"
#include "qmlsearchmodel.h"

// Constructor:
QMLTab::QMLTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QMLTab)
{
    ui->setupUi(this);
}

// Destructor:
QMLTab::~QMLTab()
{
    delete ui;
}

// Set source:
void QMLTab::setSource(const QString &source)
{
    ui->qmlView->setSource(source);
}

// Set contect property:
void QMLTab::setContextProperty(const QString &propName, const QVariant &propValue)
{
    ui->qmlView->engine()->rootContext()->setContextProperty(propName, propValue);
}

// Set contect property:
void QMLTab::setContextProperty(const QString &propName, QObject *propValue)
{
    ui->qmlView->engine()->rootContext()->setContextProperty(propName, propValue);
}
