#include "qenvironement.h"
#include "modelhelper.h"

#include <sstream>
#include <QSaveFile>
#include <QFile>
#include <QDebug>
QEnvironement *QEnvironement::_instance = Q_NULLPTR;
QEnvironement *QEnvironement::instance(QObject *parent) {
    if (_instance == Q_NULLPTR) {
        _instance = new QEnvironement(parent);
        Q_ASSERT_X(_instance, __FUNCTION__, "Error during instance creation");
    }
    return _instance;
}

QBeacon QEnvironement::addBeacon() {
    Beacon* b = _environement->add_beacons();
    b->set_enabled(true);
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

bool QEnvironement::loadEnvironementFromFile(const QString &filename) {
    static const QString defaultPath = ModelHelper::defaultDocumentsFolder() + ENVIRONEMENT_FILENAME;
    QFile file(filename.isEmpty() ? defaultPath : filename);
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        const QByteArray data = file.readAll();
        file.close();
        _environement->Clear();
        return _environement->ParseFromArray(data, data.size());
    }
    return false;
}

bool QEnvironement::saveEnvironementInFile(const QString &filename) const {
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


QEnvironement::QEnvironement(QObject *parent) : QObject(parent) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

QEnvironement::~QEnvironement() {
    _environement->Clear();
    _wrappedBeacons.clear();
}
