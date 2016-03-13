#include "stringhunter.h"
#include "helper.h"
#include <QTextStream>
#include <QScriptEngine>
#include <QDebug>

// Constructor:
StringHunter::StringHunter(const QDir &srcDir, const QStringList &filters, const QString &targetString) : mSrcDir(srcDir),
    mTargetString(targetString), mMinSize(0), stop(false)
{
    // Auto delete:
    setAutoDelete(true);

    // Search:
    Helper::files(srcDir.absolutePath(), mTargetFiles, filters);
}

// Constructor:
StringHunter::StringHunter(const QDir &srcDir, const QStringList &filters, const QStringList &targetStrings, int minSize) : mSrcDir(srcDir),
    mTargetString(""), mTargetStrings(targetStrings), mMinSize(minSize)
{
    // Auto delete:
    setAutoDelete(true);

    // Search:
    Helper::files(srcDir.absolutePath(), mTargetFiles, filters);
}

// Destructor:
StringHunter::~StringHunter()
{

}

// Run:
void StringHunter::run()
{
    if (!mTargetString.isEmpty())
    {
        // Split:
        for (int i=0; i<mTargetFiles.size(); i++)
        {
            if (stop)
                break;

            QFile file(mTargetFiles[i]);
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                continue;

            QTextStream in(&file);
            int lineNumber = 0;
            while (!in.atEnd()) {
                QString line = in.readLine();

                if (line.contains(mTargetString, Qt::CaseInsensitive))
                    emit resultAvailable(mTargetFiles[i], lineNumber, line.simplified(), mTargetString);

                lineNumber++;
            }
            file.close();

            emit progressChanged((double)i/(double)mTargetFiles.size());
        }
    }
    else
        if (!mTargetStrings.isEmpty())
        {
            for (int i=0; i<mTargetFiles.size(); i++)
            {
                if (stop)
                    break;

                QFile file(mTargetFiles[i]);
                if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
                    continue;

                QTextStream in(&file);
                int lineNumber = 0;
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    for (int j=0; j<mTargetStrings.size(); j++)
                    {
                        bool condition = line.contains(mTargetStrings[j], Qt::CaseInsensitive) && (mTargetStrings[j].length() >= mMinSize);
                        if (condition)
                            emit resultAvailable(mTargetFiles[j], lineNumber, line.simplified(), mTargetStrings[j]);
                    }

                    lineNumber++;
                }
                file.close();

                emit progressChanged((double)i/(double)mTargetFiles.size());
            }
        }

    emit finished();
}
