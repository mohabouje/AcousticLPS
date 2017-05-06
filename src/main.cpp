#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "config.h"
#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);
    a.setStyle(QStyleFactory::create("fusion"));

    MainWindow w;
    w.show();
    return a.exec();
}
#endif

