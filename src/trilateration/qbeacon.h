#ifndef QBEACON_H
#define QBEACON_H

#include <QObject>
#include <QPoint>
#include <QUuid>
#include <beacon.h>

class QBeacon : private Beacon {
public:
    QBeacon();
    static QBeacon createBeacon(const QPoint& position, int identifier = 0);

    QPoint position() const;
    void setPosition(const QPoint& point);

    QUuid universalUniqueIdentifier() const;
    void setUniversalUniqueIdentifier(const QUuid& uuid);

    int identifier() const;
    void setIdentifier(int id);
private:
    friend class QMeasure;
};

#endif // QBEACON_H
