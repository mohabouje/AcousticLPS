#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

#if !TESTING_ENABLED
    w.show();
#endif
    return a.exec();
}
