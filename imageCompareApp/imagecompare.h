#ifndef IMAGECOMPARE_H
#define IMAGECOMPARE_H
#include <QObject>
#include "iservice.h"
#include "mainwindow.h"
class Controller;

// Main application:
class ImageCompare : public QObject, public IService
{
    Q_OBJECT

public:
    // Return an instance of ImageCompare:
    static ImageCompare *instance();

    // Startup:
    virtual bool startup();

    // Shutdown:
    virtual void shutdown();

    // Destructor:
    virtual ~ImageCompare() {

    }

private:
    // Constructor:
    ImageCompare(QObject *parent=0);

private:
    // ImageCompare singleton:
    static ImageCompare *sImageCompare;

    // Controller singleton:
    Controller *mController;

    // View:
    MainWindow mMainWindow;
};

#endif // IMAGECOMPARE_H
