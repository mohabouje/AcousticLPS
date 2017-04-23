#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <trilateration/qtrilateration.h>

#include <QDebug>
#include <QVector>
#include <QPair>
#include <QFile>
#include <QUrl>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <catch.hpp>
SCENARIO("Testing the trilateration algorithm", "[QTrilateration]") {
    GIVEN("A set of beacons") {
        QVector<Point> beaconPositions;

        QFile file (":/testdata.txt");
        const bool opened = file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        while (!in.atEnd()) {
          const QString line = in.readLine();
          const QStringList coordinates = line.split("\t");
          REQUIRE(coordinates.size() == QTrilateration::AxisCount);
          Point pos;
          for (int i=QTrilateration::AxisX; i<QTrilateration::AxisCount; i++) {
              bool ok = false;
              pos(i) = QString(coordinates.at(i)).toFloat(&ok);
              REQUIRE(ok);
          }
          beaconPositions.append(pos);
        }
        file.close();
        REQUIRE(opened);
        REQUIRE(!beaconPositions.isEmpty());




        QTrilateration* trilateration = new QTrilateration();
       // trilateration->setBeacons(beacons);
        //trilateration->setMeasures(measures);

        WHEN("We stimate the point") {
            QTrilateration::Error errorCode = trilateration->calculatePosition(QTrilateration::LinearLeastSquares);
            THEN("We got no error") {
                REQUIRE(errorCode == QTrilateration::NoError);
            }
            AND_THEN("The estimated point is:") {

            }
        }
    }
}
