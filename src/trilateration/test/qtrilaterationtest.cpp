#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <trilateration/qtrilateration.h>

#include <QDebug>
#include <QVector>
#include <QPair>
#include <QFile>
#include <QUrl>
#include <QTextStream>
#include <catch.hpp>
SCENARIO("Testing the trilateration algorithm", "[QTrilateration]") {
    GIVEN("A set of beacons") {
        QFile file (":/testdata.txt");
        const bool opened = file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        while (!in.atEnd()) {
          const QString line = in.readLine();
          const QStringList coordinates = line.split("\t");
          foreach (const QString& coordinate, coordinates) {

          }
        }
        file.close();
        REQUIRE(opened);




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
