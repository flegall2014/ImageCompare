#ifndef IMAGEMODELFILTER_H
#define IMAGEMODELFILTER_H
#include <QSortFilterProxyModel>
class Controller;

class ImageModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int nCols READ nCols NOTIFY nColsChanged)

public:
    // Constructor:
    ImageModelFilter(QObject *parent=0);

    // Destructor:
    virtual ~ImageModelFilter();

    // Set controller:
    void setController(Controller *controller);

    // Accept row?
    virtual bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    // Set active filter:
    void setActiveFilter(int activeFilter);

    // Get image:
    Q_INVOKABLE QString getImage(int row, int col) const;

    // Get image weight:
    Q_INVOKABLE int getImageWeight(int row, int col) const;

    // Get dir name:
    Q_INVOKABLE QString getDirName(int col) const;

    // Get dir id:
    Q_INVOKABLE QString getDirId(int col) const;

    // Get image actual casing:
    Q_INVOKABLE QString getImageActualCasing(int row, int col);

private:
    // Return number of columns:
    int nCols() const;

private:
    // Controller:
    Controller *mController;

    // Active filter:
    int mActiveFilter;

signals:
    // NCols changed:
    void nColsChanged();
};

#endif // IMAGEMODELFILTER_H
