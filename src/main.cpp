#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "mainwindow.h"
#include <trilateration/qbeacon.h>
#include <trilateration/qmeasure.h>
#include <QApplication>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
#endif

