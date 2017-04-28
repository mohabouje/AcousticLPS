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

    _disabledSymbol->setStyle(QwtSymbol::Ellipse);
    _disabledSymbol->setPen(Qt::black);
    _disabledSymbol->setBrush(QBrush(Qt::gray));
    _disabledSymbol->setSize(QSize(15, 15));
    _disabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _disabledBeacons->setSymbol(_disabledSymbol);
    _disabledBeacons->attach(ui->environementPlot);

    _enabledSymbol->setStyle(QwtSymbol::Ellipse);
    _enabledSymbol->setPen(Qt::black);
    _enabledSymbol->setBrush(QBrush(Qt::cyan));
    _enabledSymbol->setSize(QSize(15, 15));
    _enabledBeacons->setStyle(QwtPlotCurve::NoCurve);
    _enabledBeacons->setSymbol(_enabledSymbol);
    _enabledBeacons->attach(ui->environementPlot);

    ui->environementPlot->setAxisAutoScale(QwtPlot::xBottom, false);
    ui->environementPlot->setAxisAutoScale(QwtPlot::yLeft, false);
    ui->environementPlot->setAxisScale(QwtPlot::xBottom, 0, QEnvironementInstance->width());
    ui->environementPlot->setAxisScale(QwtPlot::yLeft, 0, QEnvironementInstance->width());

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
        ui->environementPlot->setAxisScale(QwtPlot::xBottom, 0, value);
        ui->environementPlot->replot();
    });

    connect(ui->lengthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setLength(value);
        ui->yValue->setMaximum(value);
        ui->environementPlot->setAxisScale(QwtPlot::yLeft, 0, value);
        ui->environementPlot->replot();
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
        beaconsPanel()->invalidate();
        repaintEnvironement();
    });

    connect(beaconsPanel(), &BeaconsPanel::beaconEdited, [&](const QBeacon& beacon){
        Q_UNUSED(beacon);
        repaintEnvironement();
    });
}

void QEnvironementEditor::repaintEnvironement() {
    const int N = QEnvironementInstance->beaconsCount();
    QVector<double> xEnabled, yEnabled, xDisabled, yDisabled;
    QPolygonF points;
    for (int i=0; i<N; i++) {
        const QBeacon beacon = QEnvironementInstance->beaconAt(i);
        const Position point = beacon->position();
        if (beacon->isEnabled()) {
            xEnabled.append(point(0));
            yEnabled.append(point(1));
        } else {
            xDisabled.append(point(0));
            yDisabled.append(point(1));
        }
    }
    _enabledBeacons->setSamples(xEnabled, yEnabled);
    _disabledBeacons->setSamples(xDisabled, yDisabled);
    ui->environementPlot->replot();
}

QEnvironementEditor::~QEnvironementEditor() {
    delete _enabledBeacons;
    delete _enabledSymbol;
    delete ui;
}

BeaconsPanel *QEnvironementEditor::beaconsPanel() const {
    return ui->beaconsPanel;
}

