#ifndef QBEACON_H
#define QBEACON_H

#include <QObject>
#include <QPointF>
#include <QUuid>
#include <beacon.h>

class QBeacon {
public:
    QBeacon();
    static QBeacon createBeacon(const QPointF& position, int identifier = 0);
    inline QPointF position() const { return _position; }
    inline QUuid universalUniqueIdentifier() const { return _uuid; }
    inline int identifier() const { return _identifier; }
    inline bool operator==(const QBeacon& beacon) const {
        return _identifier == beacon._identifier
                && _position == beacon._position
                && _uuid == beacon._uuid;
    }
    inline bool operator!=(const QBeacon& beacon) const {
        return !(*this == beacon);
    }
    inline bool operator<(const QBeacon& beacon) const {
        return _identifier < beacon._identifier
                || _uuid < beacon._uuid;
    }
    inline bool operator>(const QBeacon& beacon) const {
        return !(*this < beacon);
    }
    void setPosition(const QPointF& point);
    void setUniversalUniqueIdentifier(const QUuid& uuid);
    void setIdentifier(int id);
private:
    QPointF         _position;
    QUuid           _uuid;
    int             _identifier;
};

inline uint qHash(const QBeacon &f) {
    return qHash(f.universalUniqueIdentifier());
}

#endif // QBEACON_H
