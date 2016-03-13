#include "ReportMgr.h"
#include "utils.h"
#include "node.h"
#include "ifilter.h"
#include "controller.h"
#include <QSettings>
#include <QDebug>

// Constructor:
ReportMgr::ReportMgr(QObject *parent) : QObject(parent),
    mController(0)
{

}

// Set controller:
void ReportMgr::setController(Controller *controller)
{
    mController = controller;
}

// Startup:
bool ReportMgr::startup()
{
    // Do we have an ini folder?
    QDir appDir = Utils::appDir();
    appDir.cdUp();
    if (!appDir.cd("report"))
        appDir.mkdir("ini");

    return true;
}

// Shutdown:
void ReportMgr::shutdown()
{
}

// Save report:
void ReportMgr::saveReport(Node *problematicNode, const QList<IFilter *> &filters, const QList<QDir> &imageDirList)
{
    // Check node:
    if (!problematicNode)
        return;

    // Check directories:
    if (imageDirList.isEmpty())
        return;

    // No problem:
    int nNodes = problematicNode->childCount();
    if (nNodes == 0)
        return;

    QStringList report;
    QString separator = " ; ";
    report << "TARGET DIRECTORIES" << "\n";

    for (int i=0; i<imageDirList.size(); i++)
        report << imageDirList[i].absolutePath() << "\n";

    report << "\n";

    // Get filters:
    QStringList filterLabels;
    filterLabels << "Path";
    for (int i=0; i<filters.size(); i++)
    {
        // Check filter:
        IFilter *filter = filters[i];
        if (!filter)
            continue;
        if (!filter->reportProblem())
            continue;
        filterLabels << filter->label();
    }
    report << filterLabels.join(separator) << "\n";
    QMap<int, int> globalStatus;

    for (int i=0; i<nNodes; i++)
    {
        // Get node:
        Node *node = problematicNode->child(i);
        if (!node)
            continue;

        // Get filter status:
        QBitArray filterStatus = node->filterStatus();
        QStringList nodeReport;
        nodeReport << node->fullRelativePath();
        for (int j=0; j<filterStatus.size(); j++)
        {
            if (j > (filters.size()-1))
                continue;
            if (!filters[j]->reportProblem())
                continue;
            nodeReport << (filterStatus[j] ? "true" : "false");
            if (filterStatus[j])
                globalStatus[j]++;
        }
        report << nodeReport.join(separator) << "\n";
    }

    // Get report dir:
    QDir reportDir = Utils::reportDir();

    // Build report file name:
    QString reportFileName = "report_" + Utils::currentDateSuffix() + ".csv";

    // Get report file path:
    QString reportFile = reportDir.absoluteFilePath(reportFileName);
    qDebug() << "SAVING REPORT TO: " << reportFile;

    // Create a new file
    QFile file(reportFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for (int i=0; i<report.size(); i++)
        out << report[i];
    out << "\n";

    for (QMap<int, int>::iterator it=globalStatus.begin(); it!=globalStatus.end(); ++it)
    {
        int filterIndex = it.key();
        if ((filterIndex < 0) || (filterIndex > (filters.size()-1)))
            continue;
        IFilter *filter = filters[filterIndex];
        if (!filter)
            continue;
        out << filter->label() << ": " << it.value() << "\n";
    }
    file.close();

    mController->openTextEditor(reportFile, reportFile);
}

// Save report:
void ReportMgr::saveReport(const QHash<QString, QStringList> &stats, const QList<QDir> &imageDirList)
{
    // Empty stats:
    if (stats.isEmpty())
        return;

    // No dir:
    if (imageDirList.isEmpty())
        return;

    QStringList report;
    report << "TARGET DIRECTORIES" << "\n";

    for (int i=0; i<imageDirList.size(); i++)
        report << imageDirList[i].absolutePath() << "\n";

    report << "\n";

    for (QHash<QString, QStringList>::const_iterator it=stats.begin(); it!=stats.end(); ++it)
    {
        qint64 sizeOnDisk = 0;
        for (int i=0; i<it.value().size(); i++)
        {
            QString file = it.value()[i];
            QFileInfo fi(file);
            sizeOnDisk += fi.size();
        }

        QString extension = "*."+it.key() + ": ";
        report << extension << QString::number(it.value().size()) << "\t\t\t\t\t SIZE ON DISK: " << QString::number(sizeOnDisk) << " (Kb) \n";
    }

    report << "\n";

    for (QHash<QString, QStringList>::const_iterator it=stats.begin(); it!=stats.end(); ++it)
    {
        QString extension = "*."+it.key();
        report << "************************************************************************** " + extension + " **************************************************************************" + "\n";
        for (int i=0; i<it.value().size(); i++)
            report << it.value()[i] << "\n";
        report << "\n";
    }

    // Get report dir:
    QDir reportDir = Utils::reportDir();

    // Build report file name:
    QString reportFileName = "report_" + Utils::currentDateSuffix() + ".csv";

    // Get report file path:
    QString reportFile = reportDir.absoluteFilePath(reportFileName);
    qDebug() << "SAVING REPORT TO: " << reportFile;

    // Create a new file
    QFile file(reportFile);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    for (int i=0; i<report.size(); i++)
        out << report[i];
    file.close();

    mController->openTextEditor(reportFile, reportFile);
}
