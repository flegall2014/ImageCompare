#include "imagecompare.h"
#include "controller.h"
#include <QDebug>

ImageCompare *ImageCompare::sImageCompare = 0;

// Constructor:
ImageCompare::ImageCompare(QObject *parent)
{
    Q_UNUSED(parent);
    mController = new Controller(this);
}

// Return kemanage singleton:
ImageCompare *ImageCompare::instance()
{
    if (!sImageCompare)
        sImageCompare = new ImageCompare();

    return sImageCompare;
}

// Startup:
bool ImageCompare::startup()
{
    // Start controller:
    if (!mController->startup())
        return false;

    // Set controller on main window:
    mMainWindow.setController(mController);

    // Show main window:
    mMainWindow.showMaximized();

    return true;
}

// Shutdown:
void ImageCompare::shutdown()
{
    qDebug() << "SHUT DOWN APP";
    mController->shutdown();
}
