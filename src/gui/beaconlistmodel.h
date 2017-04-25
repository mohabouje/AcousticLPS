#ifndef BEACONLISTMODEL_H
#define BEACONLISTMODEL_H

#include <QAbstractTableModel>
class BeaconListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BeaconListModel(QObject *parent = 0);
    enum Columns { StateColumn = 0, SNRColumn,  NameColumn, ColumnSize };
protected:
    inline int columnCount(const QModelIndex&) const Q_DECL_OVERRIDE { return ColumnSize; }
    int rowCount(const QModelIndex&) const Q_DECL_OVERRIDE;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // BEACONLISTMODEL_H
