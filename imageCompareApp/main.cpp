#include "mainwindow.h"
#include <QApplication>
#include "imagecompare.h"
#include "utils.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString data = "A";
    data.append("B");
    qDebug() << data;

    // Launch application:
    ImageCompare *imageCompare = ImageCompare::instance();
    if (!imageCompare)
        return 0;

     // Start imageCompare:
    if (imageCompare->startup())
        // Run:
        app.exec();

    // Shutdown:
    imageCompare->shutdown();

    // Delete imageCompare:
    delete imageCompare;

    return 1;
}
