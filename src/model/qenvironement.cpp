#include "qenvironement.h"
#include "modelhelper.h"

#include <sstream>
#include <QSaveFile>
#include <QFile>
#include <QDebug>

QEnvironement::QEnvironement() {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    _environement->set_width(DefaultWidth);
    _environement->set_height(DefaultHeight);
    _environement->set_length(DefaultLength);
}

QEnvironement::~QEnvironement() {
    _environement->Clear();
    _wrappedBeacons.clear();
}


QBeacon QEnvironement::addBeacon() {
    Beacon* beacon = _environement->add_beacons();
    beacon->set_uuid(QUuid::createUuid().toString().toStdString());
    beacon->set_enabled(true);
    beacon->set_snr(0);
    beacon->set_x(0);
    beacon->set_y(0);
    beacon->set_z(0);
    return beaconAt(_environement->beacons_size() - 1);
}

bool QEnvironement::removeBeacon(const QBeacon &beacon) {
    if (beacon) {
        Beacon* pointer = qSharedPointerDynamicCast<BeaconWrapper>(beacon)->pointer();
        // remove;
        return true;
    }
    return false;
}

QBeacon QEnvironement::beaconAt(int index) {
    Beacon* beacon = _environement->mutable_beacons(index);
    const QUuid uuid(QString::fromStdString(beacon->uuid()));
    if (_wrappedBeacons.contains(uuid)) {
        return _wrappedBeacons.value(uuid);
    }
    const QBeacon shared(new BeaconWrapper(beacon));
    _wrappedBeacons.insert(uuid, shared);
    return shared;
}

void QEnvironement::setLength(Real value) {
    _environement->set_length(value);
}

void QEnvironement::setWidth(Real value) {
    _environement->set_width(value);
}

void QEnvironement::setHeight(Real value) {
    _environement->set_height(value);
}

bool QEnvironement::loadEnvironementFromFile(const QString &filename) {
    static const QString defaultPath = ModelHelper::defaultDocumentsFolder() + ENVIRONEMENT_FILENAME;
    QFile file(filename.isEmpty() ? defaultPath : filename);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        const QByteArray data = file.readAll();
        file.close();
        return _environement->ParseFromArray(data, data.size());
    }
    return false;
}

bool QEnvironement::saveEnvironementInFile(const QString &filename) const {
    if (!_environement->IsInitialized()) {
        return false;
    }

    static const QString defaultPath = ModelHelper::defaultDocumentsFolder() + ENVIRONEMENT_FILENAME;
    QSaveFile file(filename.isEmpty() ? defaultPath : filename);
    if (file.open(QIODevice::WriteOnly)) {
        std::ostringstream out;
        _environement->SerializeToOstream(&out);
        const QByteArray data(out.str().c_str());
        if (file.write(data) > -1) {
            return file.commit();
        }
    }
    return false;
}


