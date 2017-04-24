#ifndef BEACONLISTMODEL_H
#define BEACONLISTMODEL_H
#include <trilateration/qbeacon.h>
#include <QAbstractListModel>
class BeaconListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit BeaconListModel(QObject *parent = 0);
    inline const QBeacon& beacon(int index) const { return _beacons.at(index); }
    inline const QList<QBeacon>& beacons() const { return _beacons; }
    inline int rowCount(const QModelIndex&) const { return _beacons.size(); }
    bool remove(const QBeacon& beacon);
    void insert(const QBeacon& beacon);
    void insert(const QList<QBeacon>& beacons);
protected:
    QVariant data(const QModelIndex &index, int role) const;
private:
    QList<QBeacon>  _beacons;
};

#endif // BEACONLISTMODEL_H
