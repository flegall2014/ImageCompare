#include "utils.h"
#include "node.h"
#include "defs.h"
#include "ifilter.h"
#include <QDirIterator>
#include <QUrl>
#include <qDebug>
#include <QDateTime>
#include <QFileSystemWatcher>

// File statistics:
void Utils::statistics(const QList<QDir> &srcDirectories, QHash<QString, QStringList> &files)
{
    QStringList imageFilter;
    imageFilter << "*";
    for (int i=0; i<srcDirectories.size(); i++)
    {
        QString srcDir = srcDirectories[i].absolutePath();
        QDirIterator it(srcDir, imageFilter, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext())
        {
            QString srcFile = it.next();
            QFileInfo fi(srcFile);
            files[fi.suffix()] << srcFile;
        }
    }
}

// Get files  recursively:
void Utils::files(const QString &srcDir, QSet<QString> &files, const QStringList &imageFilters, bool simplified)
{
    files.clear();
    if (imageFilters.isEmpty())
        return;

    QString toUse = srcDir;
    if (!toUse.endsWith("/"))
        toUse += "/";

    QDirIterator it(srcDir, imageFilters, QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext())
    {
        QString srcFile = it.next();
        if (simplified)
            srcFile.replace(toUse, "");
        files << srcFile;
    }
}

// Return simplified version of input string:
QString Utils::getKey(const QString &input)
{
    return input.simplified().toLower();
}

// Return app dir:
QDir Utils::appDir()
{
    return QDir(QCoreApplication::applicationDirPath());
}

// Return preference dir:
QDir Utils::preferenceDir()
{
    // Read preferences.ini:
    QDir tmp = appDir();
    tmp.cdUp();
    tmp.cd("ini");
    return tmp;
}

// Return report dir:
QDir Utils::reportDir()
{
    // Read preferences.ini:
    QDir tmp = appDir();
    tmp.cdUp();
    tmp.cd("report");
    return tmp;
}

// Local file?
bool Utils::isLocalFile(const QString &input)
{
    QUrl url(input);
    return url.isLocalFile();
}

// To local file:
QString Utils::toLocalFile(const QString &input)
{
    QUrl url(input);
    return Utils::isLocalFile(input) ? url.toLocalFile() : input;
}

// From local file:
QString Utils::fromLocalFile(const QString &input)
{
    QUrl url(input);
    return !url.isLocalFile() ? QUrl::fromLocalFile(input).toString() : input;
}

// Process single file:
void Utils::processSingleFile(const QString &file, QHash<QString, Node *> &allNodes, QHash<QString, Node *> &imageNodes, Node *imageRootNode)
{
    QStringList splitted = file.split("/");
    int nParts = splitted.size();
    if (nParts < 1)
        return;

    QString target = "";
    QString parentId = "";
    Node *newNode = 0;
    for (int j=0; j<nParts; j++)
    {
        // Build target:
        target += splitted[j];
        if (j < (nParts-1))
            target += "/";

        // Already created:
        if (allNodes.contains(target))
        {
            parentId = target;
            continue;
        }

        // Get parent node:
        Node *parentNode = allNodes[parentId];
        if (!parentNode)
            parentNode = imageRootNode;

        // Create node:
        QString fullRelativePath = target;
        if (fullRelativePath.endsWith("/"))
            fullRelativePath = fullRelativePath.left(target.length()-1);
        QFileInfo fi(fullRelativePath);
        bool isDir = fi.suffix().isEmpty();

        newNode = new Node(fullRelativePath, isDir ? Node::DIR:Node::IMAGE);
        parentNode->addChild(newNode);
        allNodes[target] = newNode;

        if (!isDir)
            imageNodes[fullRelativePath] = newNode;

        // Set parent:
        parentId = target;
    }
}

// Process single file:
void Utils::processSingleFile(const QString &file, QHash<QString, Node *> &imageNodes, Node *imageRootNode)
{
    // Check image root node:
    if (!imageRootNode)
        return;

    // Create node:
    QString fullRelativePath = file;
    if (fullRelativePath.endsWith("/"))
        fullRelativePath = fullRelativePath.left(file.length()-1);
    QFileInfo fi(fullRelativePath);
    bool isDir = fi.suffix().isEmpty();

    Node *newNode = new Node(fullRelativePath, isDir ? Node::DIR:Node::IMAGE);
    imageRootNode->addChild(newNode);

    if (!isDir)
        imageNodes[fullRelativePath] = newNode;
}

// Build tree:
Node *Utils::buildTree(const QList<QDir> &imageDir, const QStringList &imageFilter, QHash<QString, Node *> &imageNodes, bool ambiance1Only)
{
    // All nodes:
    QHash<QString, Node *> allNodes;

    // Root node:
    Node *rootNode = new Node("", Node::DIR);

    // Ambiance node:
    Node *imageRootNode = new Node("ROOT", Node::DIR, true);
    rootNode->addChild(imageRootNode);

    QTime time1;
    time1.start();
    QSet<QString> allFiles;
    for (int i=0; i<imageDir.size(); i++)
    {
        QSet<QString> srcFiles;
        Utils::files(imageDir[i].absolutePath(), srcFiles, imageFilter, true);
        allFiles.unite(srcFiles);
    }
    qDebug() << "ICI: " << time1.elapsed();

    QTime time2;
    time2.start();
    QSetIterator<QString> i(allFiles);
    while (i.hasNext())
    {
        QString srcFile = i.next();

        if (ambiance1Only && srcFile.contains("ambiance_", Qt::CaseInsensitive))
            if (!srcFile.contains("ambiance_1", Qt::CaseInsensitive))
                continue;
        processSingleFile(Utils::getKey(srcFile), allNodes, imageNodes, imageRootNode);
    }
    qDebug() << "LA: " << time2.elapsed();

    return rootNode;
}

// Extract subvector:
QStringList Utils::subVector(const QStringList &vec, int from, int to)
{
    QStringList subvec;
    for (int i=from; i<=to; ++i)
        subvec << vec[i];
    return subvec;
}

// Reserved picto: (TO DO, need improvement)
bool Utils::isReservedPicto(const QString &pictoPath)
{
    if (pictoPath.compare(UNKNOWN_PICTO, Qt::CaseInsensitive) == 0)
        return true;
    if (pictoPath.compare(BLUE_FOLDER_PICTO, Qt::CaseInsensitive) == 0)
        return true;
    if (pictoPath.compare(GREEN_FOLDER_PICTO, Qt::CaseInsensitive) == 0)
        return true;
    if (pictoPath.compare(RED_FOLDER_PICTO, Qt::CaseInsensitive) == 0)
        return true;

    return false;
}

// Evaluate filters:
QBitArray Utils::evaluateFilters(const QString &nodeFullRelativePath, const QList<QDir> &directories, const QList<IFilter *> &filters, bool &nodeHasProblem)
{
    QBitArray results;
    results.resize(filters.size());

    bool imageSimilar = false;
    nodeHasProblem = false;

    // Prepare results:
    for (int i=0; i<filters.size(); i++)
    {
        // Get filter:
        IFilter *filter = filters[i];
        if (!filter)
            continue;

        QString filterID = filter->_id;
        bool isMissingFilter = filterID.compare("MissingFilter", Qt::CaseInsensitive) == 0;
        bool isCorruptedFilter = filterID.compare("CorruptedFilter", Qt::CaseInsensitive) == 0;
        bool isOKFilter = filterID.compare("OKFilter", Qt::CaseInsensitive) == 0;
        bool isKOFilter = filterID.compare("KOFilter", Qt::CaseInsensitive) == 0;

        // Get results:
        results[i] = filters[i]->execute(directories, nodeFullRelativePath);
        if (filters[i]->reportProblem() && results[i])
            nodeHasProblem = true;

        // Image is missing or corrupted, no need to go further:
        if (results[i] && (isMissingFilter || isCorruptedFilter))
            break;

        // Image similar?
        if (isOKFilter)
            imageSimilar = results[i];

        // Images are similar, no need to know if they are different:
        if (isKOFilter)
            results[i] = !imageSimilar;
    }

    return results;
}

// Get actual casing:
QString Utils::getActualCasing(const QString &inputFile, const QStringList &imageFilter)
{
    // Reserved picto?
    if (Utils::isReservedPicto(inputFile))
        return "";

    // Local file?
    bool isLocal = Utils::isLocalFile(inputFile);
    QString toUse = inputFile;
    if (isLocal)
        toUse = toLocalFile(inputFile);

    QFileInfo fi(toUse);
    if (!fi.exists())
        return inputFile;

    // Get file dir:
    QDir fileDir = fi.absoluteDir();

    QString actualCaseFile = "";
    QList<QFileInfo> info = fileDir.entryInfoList(imageFilter);
    for (int i=0; i<info.size(); i++)
    {
        if (info[i].absoluteFilePath().compare(toUse, Qt::CaseInsensitive) == 0)
        {
            actualCaseFile = info[i].absoluteFilePath();
            break;
        }
    }

    if (actualCaseFile.isEmpty())
        return inputFile;
    return isLocal ? Utils::fromLocalFile(actualCaseFile) : actualCaseFile;
}

// Check images directory:
bool Utils::checkImagesDirectory(const QDir &imagesDir, QList<QDir> &ambianceDir)
{
    QDir tmp = imagesDir;
    QFileInfoList dirContents = tmp.entryInfoList(QDir::AllDirs);
    for (int i=0; i<dirContents.size(); i++)
    {
        QDir dir(dirContents[i].absoluteFilePath());
        QString dirName = dir.dirName();
        if (dirName.contains("ambiance_", Qt::CaseInsensitive))
            ambianceDir << dir;
    }

    return !ambianceDir.isEmpty();
}

// Return problem list for given node:
QStringList Utils::problemList(Node *node, const QList<IFilter *> &filters)
{
    // Check node:
    if (!node || !node->hasProblem())
        return QStringList();

    // Get filter status:
    QBitArray filterStatus = node->filterStatus();

    // Build problem list:
    QStringList problems;

    for (int i=0; i<filters.size(); i++)
    {
        // Get filter:
        IFilter *filter = filters[i];
        if (!filter)
            continue;
        if (i > (filterStatus.size()-1))
            continue;
        // Does it report problem?
        if (filter->reportProblem() && filterStatus[i])
            problems << filter->label();
    }

    return problems;
}

// Return current date suffix:
QString Utils::currentDateSuffix()
{
    QString sep = "_";
    QDateTime current = QDateTime::currentDateTime();
    int day = current.date().day();
    int month = current.date().month();
    int year = current.date().year();
    int hour = current.time().hour();
    int minute = current.time().minute();
    int sec = current.time().second();
    return QString::number(day)+sep+QString::number(month)+sep+QString::number(year)+sep+
            QString::number(hour)+sep+QString::number(minute)+sep+QString::number(sec);
}
