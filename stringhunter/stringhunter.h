#ifndef STRINGHUNTER_H
#define STRINGHUNTER_H
#include <QObject>
#include <QRunnable>
#include <QDir>
#include <QVector>

class StringHunter : public QObject, public QRunnable
{
    Q_OBJECT

public:
    // Constructor:
    StringHunter(const QDir &srcDir, const QStringList &filters, const QString &targetString);

    // Constructor:
    StringHunter(const QDir &srcDir, const QStringList &filters, const QStringList &targetStrings, int minSize=1);

    // Destructor:
    virtual ~StringHunter();

    // Run:
    virtual void run();

    // Stop?
    bool stop;

private:
    // Src dir:
    QDir mSrcDir;

    // Target string:
    QString mTargetString;

    // Target string:
    QStringList mTargetStrings;

    // QML files:
    QVector<QString> mTargetFiles;

    // Min size:
    int mMinSize;

signals:
    // Done:
    void finished();

    // Result available:
    void resultAvailable(QString, uint, QString, QString);

    // Progress changed:
    double progressChanged(double progress);
};

#endif // STRINGHUNTER_H
