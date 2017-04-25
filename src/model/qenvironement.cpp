#include "qenvironement.h"

QEnvironement *QEnvironement::_instance = Q_NULLPTR;
QEnvironement *QEnvironement::instance(QObject *parent) {
    if (_instance == Q_NULLPTR) {
        _instance = new QEnvironement(parent);
        Q_ASSERT_X(_instance, __FUNCTION__, "Error during instance creation");
    }
    return _instance;
}

QEnvironement::QEnvironement(QObject *parent) : QObject(parent) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}

QEnvironement::~QEnvironement() {
    _environement->Clear();
}
