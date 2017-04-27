#ifndef QBEACON_H
#define QBEACON_H
#include "config.h"
#include <QMetaType>
#include <QUuid>
#include <QSharedPointer>

#include <model/model.pb.h>

class BeaconWrapper {
public:
    BeaconWrapper() {}
    BeaconWrapper(Beacon* beacon);
    inline QUuid universalUniqueIdentifier() const {  return QUuid(QString::fromStdString(_beacon->uuid())); }
    inline int identifier() const { return _beacon->id(); }
    inline QString name() const { return QString::fromStdString(_beacon->name()); }
    inline Real SNR() const { return _beacon->snr(); }
    inline bool isEnabled() const { return _beacon->enabled();}
    inline Position position() const {
        return Position({_beacon->x(), _beacon->y(), _beacon->z()});
    }
    inline bool operator==(const BeaconWrapper& beacon) const {
        return _beacon->id() == beacon._beacon->id()
                && _beacon->uuid() == beacon._beacon->uuid();
    }
    inline bool operator!=(const BeaconWrapper& beacon) const {
        return !(*this == beacon);
    }
    inline bool operator<(const BeaconWrapper& beacon) const {
        return _beacon->id() < beacon._beacon->id()
                && _beacon->uuid() < beacon._beacon->uuid();
    }
    inline bool operator>(const BeaconWrapper& beacon) const {
        return !(*this < beacon);
    }
    void setPosition(const Position& point);
    void setUniversalUniqueIdentifier(const QUuid& uuid);
    void setIdentifier(int id);
    void setName(const QString &name);
    void setSNR(const Real &SNR);
    void setEnabled(bool state);
private:
    friend class QEnvironement;

    Beacon*         _beacon;
    inline Beacon* pointer() const { return _beacon; }
};
typedef QSharedPointer<BeaconWrapper> QBeacon;
Q_DECLARE_METATYPE(QBeacon)


inline uint qHash(const QBeacon &f) {
    return qHash(f->universalUniqueIdentifier());
}

#endif // QBEACON_H
