#ifndef QBEACON_H
#define QBEACON_H
#include "config.h"
#include <QMetaType>
#include <QUuid>
#include <QVector3D>

#include <model/model.pb.h>
class QBeacon {
public:
    QBeacon();
    static QBeacon createBeacon(const Point& position, int identifier = 0);
    inline QUuid universalUniqueIdentifier() const {  return QUuid(QString::fromStdString(_beacon->uuid())); }
    inline int identifier() const { return _beacon->id(); }
    inline QString name() const { return QString::fromStdString(_beacon->name()); }
    inline Real SNR() const { return _beacon->snr(); }
    inline Position position() const {
        Point* pos = _beacon->mutable_point();
        return Position({pos->x(), pos->y(), pos->z()});
    }
    inline bool operator==(const QBeacon& beacon) const {
        return _beacon->id() == beacon._beacon->id()
                && _beacon->uuid() == beacon._beacon->uuid();
    }
    inline bool operator!=(const QBeacon& beacon) const {
        return !(*this == beacon);
    }
    inline bool operator<(const QBeacon& beacon) const {
        return _beacon->id() < beacon._beacon->id()
                && _beacon->uuid() < beacon._beacon->uuid();
    }
    inline bool operator>(const QBeacon& beacon) const {
        return !(*this < beacon);
    }
    void setPosition(const Position& point);
    void setUniversalUniqueIdentifier(const QUuid& uuid);
    void setIdentifier(int id);
    void setName(const QString &name);
    void setSNR(const Real &SNR);

private:
    Beacon*         _beacon;
};
Q_DECLARE_METATYPE(QBeacon)

inline bool operator ==(const Point& a, const Point& b) {
    return a.x() == b.x() && a.y() == b.y() && a.z() == b.z();
}

inline uint qHash(const QBeacon &f) {
    return qHash(f.universalUniqueIdentifier());
}

#endif // QBEACON_H
