#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

#include <audio/qportaudiorecorder.h>
#include <audio/qportaudioplayer.h>
#include <model/qmeasure.h>
#include <model/qenvironement.h>
#include <gui/qenvironementeditor.h>
#include <gui/helper.h>

#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Recorder;
    Player;
    Environement;

    const bool loaded = Environement->loadEnvironementFromFile();
    if (!loaded) {
        qWarning() << "Error: we could not restore the last saved environement";
    }

    ui->setupUi(this);
    initUi();
    loadUi();
    simulateMeasures();

}

void MainWindow::simulateMeasures() {
    const Size N = Environement->beaconsCount();
    QVector<QMeasure> measures(N);
    for (Size i=0; i<N; i++) {
        const QBeacon& beacon = Environement->beaconAt(i);
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

    QActionGroup* group = new QActionGroup(this);
    group->addAction(ui->actionTrack);
    group->addAction(ui->actionCorrelation);
    group->addAction(ui->actionSpectrogram);
    connect(group, &QActionGroup::triggered, [&](QAction* action) {
        if (action == ui->actionTrack) {
            ui->stackedWidget->setCurrentWidget(ui->trilaterationChart);
        } else if (action == ui->actionCorrelation) {
            ui->stackedWidget->setCurrentWidget(ui->correlationChart);
        } else if (action == ui->actionSpectrogram) {
            ui->stackedWidget->setCurrentWidget(ui->spectrogramChart);
        }
    });

    ui->bottomToolbar->addWidget(ui->waveFormChart);

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
                if (!Environement->loadEnvironementFromFile(fileName)) {
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
            if (!Environement->saveEnvironementInFile(fileName)) {
                QMessageBox::information(this, tr("Unable to open file"), "The file is corrupted");
            }
        }
    });

    connect(ui->actionNew, &QAction::triggered, [&](bool) {
        const QMessageBox::StandardButton result = QMessageBox::question(this, "Create a new environement", "Do you want to discard the current environement & create a new one? "
                                                                "All changes not saved previously will be lost.");
        if (result == QMessageBox::Yes) {
            Environement->clear();
            Environement->saveEnvironementInFile();
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

    const Real sampleRate = Recorder->sampleRate();
    const Real bufferTime = 0.1;
    Recorder->setFrameLength(bufferTime * sampleRate);


    ui->waveFormChart->setBufferSize(sampleRate, 10.0);
    ui->correlationChart->setBufferSize(sampleRate, bufferTime);
    ui->spectrogramChart->setBufferSize(sampleRate, bufferTime);

    connect(Recorder, &QPortAudioRecorder::onRecorderStarted, [&]() {
        ui->actionMicrophone->setIcon(MICRO_OFF_ICON);
    });
    connect(Recorder, &QPortAudioRecorder::onReconderStopped, [&]() {
        ui->actionMicrophone->setIcon(MICRO_ON_ICON);
    });

    connect(Recorder, SIGNAL(onBufferReady(float*,unsigned long)),
            this, SLOT(bufferReady(float*,unsigned long)), Qt::QueuedConnection);

    connect(ui->actionMicrophone, &QAction::triggered, [&](bool) {
        if (Recorder->isInitialized()) {
            const bool recording = Recorder->isRunning();
            if (recording) {
                Recorder->stop();
            } else {
                Recorder->record();
            }
        }
    });
}

void MainWindow::bufferReady(float* buffer, unsigned long size) {
    ui->waveFormChart->setData(buffer, size);
    ui->correlationChart->setData(buffer, size);
    ui->spectrogramChart->setData(buffer, size);
}

void MainWindow::loadUi() {
    QSettings settings;
    settings.beginGroup("UI");
    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray());
    restoreState(settings.value("state", saveState()).toByteArray());
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
    if (!Environement->saveEnvironementInFile()) {
        qWarning() << "Error: could not save the current data model";
    }
    saveUi();
    QMainWindow::closeEvent(event);
}

