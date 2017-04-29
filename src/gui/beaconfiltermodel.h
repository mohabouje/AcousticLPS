#ifndef BEACONSortMODEL_H
#define BEACONSortMODEL_H

#include <QSortFilterProxyModel>
class BeaconFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit BeaconFilterModel(QObject *parent = 0);
    enum SortType { SortByEnableState = 0, SortBySNR, SortByName  };
    inline SortType Sort() const { return _currentSort; }
    inline QString filterName() const { return _filterName; }
    void setSort(const SortType &Sort);
    void setFilterName(const QString &filterName);
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;
private:
    SortType    _currentSort{SortByEnableState};
    QString     _filterName;
};

#endif // BEACONSortMODEL_H
