#ifndef TREEMODELFILTER_H
#define TREEMODELFILTER_H
#include <QSortFilterProxyModel>
class Controller;

class TreeModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    // Constructor:
    TreeModelFilter(QObject *parent=0);

    // Destructor:
    virtual ~TreeModelFilter();

    // Set controller:
    void setController(Controller *controller);

    // Accept row?
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    // Accept row:
    bool acceptRow(int source_row, const QModelIndex &source_parent) const;

private:
    // Controller:
    Controller *mController;
};

#endif // TREEMODELFILTER_H
