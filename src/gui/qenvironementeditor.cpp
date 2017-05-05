#include "qenvironementeditor.h"
#include "ui_qenvironementeditor.h"
#include "helper.h"
#include <model/qenvironement.h>

#include <QMessageBox>
#include <QUuid>
#include <QDebug>

QEnvironementEditor::QEnvironementEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QEnvironementEditor)
{
    ui->setupUi(this);
    initUi();
}

void QEnvironementEditor::initUi() {
    ui->beaconsPanel->showHeader(false);
    ui->beaconsChart->updateEnvironement();
    ui->beaconsChart->repaintBeacons();

    ui->widthValue->setValue(Environement->width());
    ui->lengthValue->setValue(Environement->length());
    ui->heightValue->setValue(Environement->height());

    connect(ui->heightValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        Environement->setHeight(value);
        ui->zValue->setMaximum(value);
    });

    connect(ui->widthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        Environement->setWidth(value);
        ui->xValue->setMaximum(value);
        ui->beaconsChart->setAxisScale(QwtPlot::xBottom, 0, value);
        ui->beaconsChart->replot();
    });

    connect(ui->lengthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        Environement->setLength(value);
        ui->yValue->setMaximum(value);
        ui->beaconsChart->setAxisScale(QwtPlot::yLeft, 0, value);
        ui->beaconsChart->replot();
    });

    connect(ui->addButton, &QToolButton::released, [&]() {
        const QString name = ui->beaconName->text();
        if (name.isEmpty()) {
            QMessageBox::information(this, "Empty name", "Please insert a valid name for the beacon");
            return;
        }

        const QBeacon beacon = Environement->addBeacon();
        beacon->setName(name);
        beacon->setPosition(Position({ui->xValue->value(),
                                      ui->yValue->value(),
                                      ui->zValue->value()}));
        ui->beaconName->clear();
        ui->xValue->setValue(0);
        ui->yValue->setValue(0);
        ui->zValue->setValue(0);
        ui->beaconsPanel->invalidate();
        ui->beaconsChart->repaintBeacons();
    });

    connect(ui->beaconsPanel, &BeaconsPanel::beaconEdited, [&](const QBeacon& beacon){
        Q_UNUSED(beacon);
        ui->beaconsChart->repaintBeacons();
    });

    connect(ui->beaconsPanel, &BeaconsPanel::beaconSelected, ui->beaconsChart, &BeaconsChart::beaconSelected);
}



QEnvironementEditor::~QEnvironementEditor() {
    delete ui;
}


