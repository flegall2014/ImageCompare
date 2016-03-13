#ifndef HELPER_H
#define HELPER_H
#include <QString>
#include <QVector>
#include <QStringList>

class Helper
{
public:
    // Recurse all files in target dir:
    static void files(const QString &srcDir, QVector<QString> &files, const QStringList &imageFilters);
};

#endif // HELPER_H
