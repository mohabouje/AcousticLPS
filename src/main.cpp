#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "config.h"
#include "mainwindow.h"

#include <gui/helper.h>
#include <math/mathutil.h>
#include <QApplication>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);

    MainWindow w;
    w.show();
    return a.exec();
}
#endif

