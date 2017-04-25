#ifndef BEACONLISTMODEL_H
#define BEACONLISTMODEL_H

#include <QAbstractListModel>
class BeaconListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BeaconListModel(QObject *parent = 0);
protected:
    enum Columns { StateColumn = 0, NameColumn, SNRColumn, ColumnSize };
    inline int columnCount(const QModelIndex&) const Q_DECL_OVERRIDE { return ColumnSize; }
    int rowCount(const QModelIndex&) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
};

#endif // BEACONLISTMODEL_H
