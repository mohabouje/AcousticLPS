#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <math/mathutil.h>
#include <model/qenvironement.h>
#include <gui/qenvironementeditor.h>

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    const bool loaded = QEnvironementInstance->loadEnvironementFromFile();
    if (!loaded) {
        qWarning() << "Error: we could not restore the last saved environement";
    }

    ui->setupUi(this);
    initUi();
    loadUi();
    simulateMeasures();
}

void MainWindow::simulateMeasures() {
    const Size N = QEnvironementInstance->beaconsCount();
    QVector<QMeasure> measures(N);
    for (Size i=0; i<N; i++) {
        const QBeacon& beacon = QEnvironementInstance->beaconAt(i);
        const QMeasure measure = QMeasure::createMeasure(beacon, 4.0, 0.0);
        measures[i] = measure;
    }

    ui->trilaterationChart->setMeasures(measures);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUi() {
    QWidget *spacerWidget = new QWidget(this);
    spacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    spacerWidget->setVisible(true);
    ui->mainToolBar->addWidget(spacerWidget);

    QLineEdit* searchLineEdit = new QLineEdit(this);
    searchLineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    searchLineEdit->setPlaceholderText("Type to filter...");
    searchLineEdit->setMaximumHeight(ui->mainToolBar->height() * 0.95);
    searchLineEdit->setMinimumWidth(150);
    connect(searchLineEdit, &QLineEdit::textChanged, [&](const QString& text) {
        ui->beaconsPanel->filterModel()->setFilterName(text);
    });
    ui->mainToolBar->addWidget(searchLineEdit);
    ui->trilaterationChart->showAxis(false);

    connect(ui->actionShowBeacons, &QAction::toggled, ui->trilaterationChart, &TrilaterationChart::showBeacons);
    connect(ui->actionShowGrid, &QAction::toggled, ui->trilaterationChart, &TrilaterationChart::showGrid);
    connect(ui->actionShowTrilateration, &QAction::toggled, ui->trilaterationChart, &TrilaterationChart::showTrilateration);

    connect(ui->actionEnvironement, &QAction::triggered, [&](bool) {
        QEnvironementEditor editor;
        editor.exec();
        ui->beaconsPanel->invalidate();
        ui->trilaterationChart->updateEnvironement();
        ui->trilaterationChart->repaintBeacons();
        ui->trilaterationChart->repaintTrilateration();
    });

    connect(ui->actionOpen, &QAction::triggered, [&](bool) {
        const QMessageBox::StandardButton result = QMessageBox::question(this, "Load an environement", "Do you want to discard the current environement & load a new one? "
                                                                "All changes not saved previously will be lost.");
        if (result == QMessageBox::Yes) {
            const QString fileName = QFileDialog::getOpenFileName(this,
                    tr("Open Environement File"), "", QString("Environement (*%1)").arg(ENVIRONEMENT_FORMAT));
            if (!fileName.isEmpty()) {
                if (!QEnvironementInstance->loadEnvironementFromFile(fileName)) {
                    QMessageBox::information(this, tr("Unable to open file"), "The file is corrupted");
                }
            }
        }
    });

    connect(ui->actionSave, &QAction::triggered, [&](bool) {
        QString fileName = QFileDialog::getSaveFileName(this,
                tr("Open Environement File"), "", QString("Environement (*%1)").arg(ENVIRONEMENT_FORMAT));

        if (!fileName.endsWith(ENVIRONEMENT_FORMAT))
            fileName += ENVIRONEMENT_FORMAT;

        if (!fileName.isEmpty()) {
            if (!QEnvironementInstance->saveEnvironementInFile(fileName)) {
                QMessageBox::information(this, tr("Unable to open file"), "The file is corrupted");
            }
        }
    });

    connect(ui->actionNew, &QAction::triggered, [&](bool) {
        const QMessageBox::StandardButton result = QMessageBox::question(this, "Create a new environement", "Do you want to discard the current environement & create a new one? "
                                                                "All changes not saved previously will be lost.");
        if (result == QMessageBox::Yes) {
            QEnvironementInstance->clear();
            QEnvironementInstance->saveEnvironementInFile();
            invalidate();
        }
    });

    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(ui->beaconsPanel, &BeaconsPanel::beaconSelected, ui->trilaterationChart, &TrilaterationChart::beaconSelected);
    connect(ui->beaconsPanel, &BeaconsPanel::beaconEdited, [&](const QBeacon& beacon){
        Q_UNUSED(beacon);
        ui->trilaterationChart->repaintBeacons();
        ui->trilaterationChart->repaintTrilateration();
    });
}

void MainWindow::loadUi() {
    QSettings settings;
    settings.beginGroup("UI");
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("state", saveState()).toByteArray());
    ui->verticalSplitter->restoreState(
                settings.value("vSplitter", ui->verticalSplitter->saveState())
                .toByteArray());
    ui->horizontalSplitter->restoreState(
                settings.value("hSplitter", ui->horizontalSplitter->saveState())
                .toByteArray());
    ui->actionShowBeacons->setChecked(settings.value("showBeacons", true).toBool());
    ui->actionShowGrid->setChecked(settings.value("showGrid", true).toBool());
    ui->actionShowTrilateration->setChecked(settings.value("showTrilateration", true).toBool());
    settings.endGroup();
}

void MainWindow::saveUi() {
    QSettings settings;
    settings.beginGroup("UI");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("state", saveState());
    settings.setValue("vSplitter", ui->verticalSplitter->saveState());
    settings.setValue("hSplitter", ui->horizontalSplitter->saveState());
    settings.setValue("showBeacons", ui->actionShowBeacons->isChecked());
    settings.setValue("showGrid", ui->actionShowGrid->isChecked());
    settings.setValue("showTrilateration", ui->actionShowTrilateration->isChecked());
    settings.endGroup();
    settings.sync();
}

void MainWindow::invalidate() {
    ui->beaconsPanel->invalidate();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if (!QEnvironementInstance->saveEnvironementInFile()) {
        qWarning() << "Error: could not save the current data model";
    }
    saveUi();
    QMainWindow::closeEvent(event);
}

