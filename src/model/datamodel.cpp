#include "datamodel.h"

DataModel *DataModel::_instance = Q_NULLPTR;
DataModel *DataModel::instance(QObject *parent) {
    if (_instance == Q_NULLPTR) {
        _instance = new DataModel(parent);
        Q_ASSERT_X(_instance, __FUNCTION__, "Error during instance creation");
    }
    return _instance;
}

DataModel::DataModel(QObject *parent) : QObject(parent) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
}
