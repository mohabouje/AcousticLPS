#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <gui/qenvironementeditor.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionEnvironement, &QAction::triggered, [&](bool) {
        QEnvironementEditor editor;
        editor.exec();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}
