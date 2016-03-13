#include "pictohunter.h"

// Constructor:
PictoHunter::PictoHunter(const QStringList &inputString, const QStringList &pictoBaseNames, const QStringList &toKeepPicto) :
    stop(false), mPictoBaseNames(pictoBaseNames), mInputString(inputString),
    mMinPictoLength(3), mToKeepPicto(toKeepPicto)
{

}

// Run:
void PictoHunter::run()
{
    for (int i=0; i<mPictoBaseNames.size(); i++)
    {
        if (stop)
            break;
        for (int j=0; j<mInputString.size(); j++)
        {
            QString inputString = mInputString[j];
            if (inputString.isEmpty())
                continue;
            bool condition1 = inputString.indexOf(mPictoBaseNames[i]) > 0;
            bool condition2 = mPictoBaseNames[i].length() <= mMinPictoLength;
            bool condition3 = mToKeepPicto.contains(mPictoBaseNames[i], Qt::CaseInsensitive);
            if (condition1 || condition2 || condition3)
                emit pictoUsed(mPictoBaseNames[i]);
        }
        emit progressChanged();
    }

    emit finished();
}
