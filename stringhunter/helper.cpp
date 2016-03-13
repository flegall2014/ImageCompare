#include "helper.h"
#include <QDirIterator>

// Get files  recursively:
void Helper::files(const QString &srcDir, QVector<QString> &files, const QStringList &imageFilters)
{
    files.clear();
    if (imageFilters.isEmpty())
        return;

    QDirIterator it(srcDir, imageFilters, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
        files << it.next();
}
