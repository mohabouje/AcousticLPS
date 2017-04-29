#ifndef BEACONLISTMODEL_H
#define BEACONLISTMODEL_H

#include <QAbstractTableModel>
class BeaconListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BeaconListModel(QObject *parent = 0);
    enum Columns { StateColumn = 0, SNRColumn,  NameColumn, ColumnSize };
    int rowCount(const QModelIndex& = QModelIndex()) const Q_DECL_OVERRIDE;
    inline int columnCount(const QModelIndex& = QModelIndex()) const Q_DECL_OVERRIDE { return ColumnSize; }
protected:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // BEACONLISTMODEL_H
