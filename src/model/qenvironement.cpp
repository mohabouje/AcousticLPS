#include "qenvironement.h"

QEnvironement *QEnvironement::_instance = Q_NULLPTR;
QEnvironement *QEnvironement::instance(QObject *parent) {
    if (_instance == Q_NULLPTR) {
        _instance = new QEnvironement(parent);
        Q_ASSERT_X(_instance, __FUNCTION__, "Error during instance creation");
    }
    return _instance;
}

QBeacon QEnvironement::addBeacon() {
    _environement->add_beacons();
    return beacon(beaconsCount() - 1);
}

QBeacon QEnvironement::beacon(int index) {
    Beacon* beacon = _environement->mutable_beacons(index);
    const QUuid uuid(QString::fromStdString(beacon->uuid()));
    if (_wrappedBeacons.contains(uuid)) {
        return _wrappedBeacons.value(uuid);
    }
    const QBeacon shared(new BeaconWrapper(beacon));
    _wrappedBeacons.insert(uuid, shared);
    return shared;
}


QEnvironement::QEnvironement(QObject *parent) : QObject(parent) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

QEnvironement::~QEnvironement() {
    _environement->Clear();
    _wrappedBeacons.clear();
}
