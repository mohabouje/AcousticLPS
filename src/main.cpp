#if TESTING_ENABLED
#include <catch_with_main.hpp>
#else
#include "config.h"
#include "mainwindow.h"

#include <gui/helper.h>
#include <QApplication>
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setApplicationName(APP_NAME);
    a.setApplicationVersion(APP_VERSION);
    a.setOrganizationName(ORGANIZATION_NAME);
    a.setOrganizationDomain(ORGANIZATION_DOMAIN);

    MainWindow w;
    w.show();

    /*const Position point = {2,5,0};
    Gui::plot(MathUtil::hiperbolicChart(point, 2, 200));*/
    return a.exec();
}
#endif

