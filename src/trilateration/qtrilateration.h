#ifndef QTRILATERATION_H
#define QTRILATERATION_H

#include <QObject>
#include <trilateration.h>

class QTrilateration : public QObject, private Trilateration
{
    Q_OBJECT
public:
    explicit QTrilateration(QObject *parent = 0);
};

#endif // QTRILATERATION_H
