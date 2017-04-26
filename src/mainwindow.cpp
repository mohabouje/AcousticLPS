#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"


#include <model/qenvironement.h>
#include <gui/qenvironementeditor.h>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    const bool loaded = QEnvironement::instance()->loadEnvironementFromFile();
    if (!loaded) {
        qWarning() << "Error: we could not restore the last saved environement";
    }

    ui->setupUi(this);
    connect(ui->actionEnvironement, &QAction::triggered, [&](bool) {
        QEnvironementEditor editor;
        editor.exec();
    });

    connect(ui->actionOpen, &QAction::triggered, [&](bool) {
        const QString fileName = QFileDialog::getOpenFileName(this,
                tr("Open Environement File"), "", QString("Environement (*%1)").arg(ENVIRONEMENT_FORMAT));
        if (!fileName.isEmpty()) {
            if (!QEnvironement::instance()->loadEnvironementFromFile(fileName)) {
                QMessageBox::information(this, tr("Unable to open file"), "The file is corrupted");
            }
        }
    });

    connect(ui->actionSave, &QAction::triggered, [&](bool) {
        QString fileName = QFileDialog::getSaveFileName(this,
                tr("Open Environement File"), "", QString("Environement (*%1)").arg(ENVIRONEMENT_FORMAT));

        if (!fileName.endsWith(ENVIRONEMENT_FORMAT))
            fileName += ENVIRONEMENT_FORMAT;

        if (!fileName.isEmpty()) {
            if (!QEnvironement::instance()->saveEnvironementInFile(fileName)) {
                QMessageBox::information(this, tr("Unable to open file"), "The file is corrupted");
            }
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::closeEvent(QCloseEvent *event) {
    if (!QEnvironement::instance()->saveEnvironementInFile()) {
        qWarning() << "Error: could not save the current data model";
    }
    QMainWindow::closeEvent(event);
}

