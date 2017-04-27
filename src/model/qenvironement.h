#ifndef DATAMODEL_H
#define DATAMODEL_H
#include "qbeacon.h"

#include <QMap>
#include <QObject>
#include <model/model.pb.h>
class QEnvironement : public QObject
{
    Q_OBJECT
public:
    static QEnvironement* instance(QObject *parent = Q_NULLPTR);
    inline QString name() const { return QString::fromStdString(_environement->name()); }
    inline Real latitude() const { return _environement->latitude(); }
    inline Real longitude() const { return _environement->longitude(); }
    inline Real  altitude() const { return _environement->altitude(); }
    inline int beaconsCount() const { return _environement->beacons_size(); }

    QBeacon addBeacon();
    bool    removeBeacon(const QBeacon& beacon);
    QBeacon beacon(int index);

public:
    bool loadEnvironementFromFile(const QString& filename = QString());
    bool saveEnvironementInFile(const QString& filename = QString()) const;
private:
    explicit QEnvironement(QObject *parent = 0);
    ~QEnvironement();
    static QEnvironement*   _instance;
    Environement*           _environement{new Environement};
    QMap<QUuid, QBeacon>    _wrappedBeacons;
};

#endif // DATAMODEL_H
