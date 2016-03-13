#ifndef UTILS_H
#define UTILS_H
#include <QStringList>
#include <QSet>
#include <QDir>
#include <QCoreApplication>
class Node;
class IFilter;

class Utils
{
public:
    // File statistics:
    static void statistics(const QList<QDir> &srcDirectories, QHash<QString, QStringList> &files);

    // Get files  recursively:
    static void files(const QString &srcDir, QSet<QString> &files, const QStringList &imageFilters,
        bool simplified=false);

    // Get key:
    static QString getKey(const QString &input);

    // Application dir:
    static QDir appDir();

    // Preference dir:
    static QDir preferenceDir();

    // Report dir:
    static QDir reportDir();

    // Local file?
    static bool isLocalFile(const QString &input);

    // To local file:
    static QString toLocalFile(const QString &input);

    // From local file:
    static QString fromLocalFile(const QString &input);

    // Process single file:
    static void processSingleFile(const QString &file, QHash<QString, Node *> &allNodes, QHash<QString, Node *> &imageNodes, Node *imageRootNode);

    // Process single file:
    static void processSingleFile(const QString &file, QHash<QString, Node *> &imageNodes, Node *imageRootNode);

    // Build tree:
    static Node *buildTree(const QList<QDir> &imageDir, const QStringList &imageFilter, QHash<QString, Node *> &imageNodes, bool ambiance1Only=false);

    // Extract subvector:
    static QStringList subVector(const QStringList &vec, int from, int to);

    // Reserved picto?
    static bool isReservedPicto(const QString &pictoPath);

    // Evaluate filters:
    static QBitArray evaluateFilters(const QString &nodeFullRelativePath, const QList<QDir> &directories, const QList<IFilter *> &filters, bool &nodeHasProblem);

    // Get actual casing:
    static QString getActualCasing(const QString &inputFile, const QStringList &imageFilter);

    // Check images directory:
    static bool checkImagesDirectory(const QDir &imagesDir, QList<QDir> &ambianceDir);

    // Return problem list for a given node:
    static QStringList problemList(Node *node, const QList<IFilter *> &filters);

    // Return current date suffix:
    static QString currentDateSuffix();
};

#endif // UTILS_H
