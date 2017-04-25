#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <model/model.pb.h>
class DataModel : public QObject
{
    Q_OBJECT
public:
    static DataModel* instance(QObject *parent = Q_NULLPTR);
private:
    explicit DataModel(QObject *parent = 0);
    static DataModel*   _instance;
};

#endif // DATAMODEL_H
