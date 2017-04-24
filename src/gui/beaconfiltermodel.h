#ifndef BEACONSortMODEL_H
#define BEACONSortMODEL_H

#include <QSortFilterProxyModel>
class BeaconFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit BeaconFilterModel(QObject *parent = 0);
    enum SortType { SortByUuid = 0, SortByName, SortByIdentifier, SortBySNR };
    inline SortType Sort() const { return _currentSort; }
    inline QString nameFilter() const { return _nameFilter; }
    void setSort(const SortType &Sort) { _currentSort = Sort; }
    void setNameFilter(const QString &nameFilter) { _nameFilter = nameFilter; }
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const Q_DECL_OVERRIDE;
private:
    SortType    _currentSort{SortByUuid};
    QString     _nameFilter;
};

#endif // BEACONSortMODEL_H
