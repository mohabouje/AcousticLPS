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
    ui->beaconsChart->setAxisScale(QwtPlot::xBottom, 0, QEnvironementInstance->width());
    ui->beaconsChart->setAxisScale(QwtPlot::yLeft, 0, QEnvironementInstance->width());
    ui->beaconsChart->repaintEnvironement();

    ui->widthValue->setValue(QEnvironementInstance->width());
    ui->lengthValue->setValue(QEnvironementInstance->length());
    ui->heightValue->setValue(QEnvironementInstance->height());

    connect(ui->heightValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setHeight(value);
        ui->zValue->setMaximum(value);
    });

    connect(ui->widthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setWidth(value);
        ui->xValue->setMaximum(value);
        ui->beaconsChart->setAxisScale(QwtPlot::xBottom, 0, value);
        ui->beaconsChart->replot();
    });

    connect(ui->lengthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setLength(value);
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

        const QBeacon beacon = QEnvironementInstance->addBeacon();
        beacon->setName(name);
        beacon->setPosition(Position({ui->xValue->value(),
                                      ui->yValue->value(),
                                      ui->zValue->value()}));
        ui->beaconName->clear();
        ui->xValue->setValue(0);
        ui->yValue->setValue(0);
        ui->zValue->setValue(0);
        ui->beaconsPanel->invalidate();
        ui->beaconsChart->repaintEnvironement();
    });

    connect(ui->beaconsPanel, &BeaconsPanel::beaconEdited, [&](const QBeacon& beacon){
        Q_UNUSED(beacon);
        ui->beaconsChart->repaintEnvironement();
    });

    connect(ui->beaconsPanel, &BeaconsPanel::beaconSelected, ui->beaconsChart, &BeaconsChart::beaconSelected);
}



QEnvironementEditor::~QEnvironementEditor() {
    delete ui;
}


