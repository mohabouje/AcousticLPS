#ifndef QBEACON_H
#define QBEACON_H

#include <QObject>
#include <QPointF>
#include <QUuid>
#include <beacon.h>

class QBeacon : public Beacon {
public:
    QBeacon();
    static QBeacon createBeacon(const QPointF& position, int identifier = 0);

    QPointF position() const;
    void setPosition(const QPointF& point);

    QUuid universalUniqueIdentifier() const;
    void setUniversalUniqueIdentifier(const QUuid& uuid);

    int identifier() const;
    void setIdentifier(int id);
private:
    friend class QMeasure;
};

#endif // QBEACON_H
