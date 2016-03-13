#ifndef PICTOHUNTER_H
#define PICTOHUNTER_H
#include <QRunnable>
#include <QObject>
#include <QStringList>

class PictoHunter : public QObject, public QRunnable
{
    Q_OBJECT

public:
    // Constructor:
    PictoHunter(const QStringList &inputString, const QStringList &pictoBaseNames, const QStringList &toKeepPicto);

    // Run:
    virtual void run();

    // Stop:
    bool stop;

private:
    // Picto base names:
    QStringList mPictoBaseNames;

    // Input string:
    QStringList mInputString;

    // Min picto length:
    int mMinPictoLength;

    // List of pictos to be kept:
    QStringList mToKeepPicto;

signals:
    // Result available:
    void pictoUsed(const QString &pictoBaseName);

    // Progress changed:
    void progressChanged();

    // Finished:
    void finished();
};

#endif // PICTOHUNTER_H
