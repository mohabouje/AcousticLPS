#include "qenvironementeditor.h"
#include "ui_qenvironementeditor.h"
#include "helper.h"
#include <model/qenvironement.h>

#include <QMessageBox>
#include <QUuid>
#include <QDebug>

QEnvironementEditor::QEnvironementEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QEnvironementEditor),
    _sourceModel(new BeaconListModel(parent)),
    _filterModel(new BeaconFilterModel(parent))
{
    ui->setupUi(this);


    filterModel()->setSourceModel(sourceModel());
    tableList()->resizeColumnsToContents();
    tableList()->setModel(filterModel());
    tableList()->horizontalHeader()->setStretchLastSection(true);
    tableList()->horizontalHeader()->setStretchLastSection(true);
    tableList()->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableList()->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableList()->setSelectionMode(QAbstractItemView::SingleSelection);
    tableList()->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableList()->setShowGrid(false);

    initUi();


}

void QEnvironementEditor::initUi() {
    ui->widthValue->setValue(QEnvironementInstance->width());
    ui->lengthValue->setValue(QEnvironementInstance->length());
    ui->heightValue->setValue(QEnvironementInstance->height());

    _dataSymbol->setStyle(QwtSymbol::Ellipse);
    _dataSymbol->setPen(Qt::red);
    _dataSymbol->setBrush(QBrush(Qt::red));
    _dataSymbol->setSize(QSize(20, 20));
    _dataPlot->setStyle(QwtPlotCurve::NoCurve);
    _dataPlot->setSymbol(_dataSymbol);
    _dataPlot->attach(ui->environementPlot);

    ui->environementPlot->setAxisAutoScale(QwtPlot::xBottom, false);
    ui->environementPlot->setAxisAutoScale(QwtPlot::yLeft, false);
    ui->environementPlot->setAxisScale(QwtPlot::xBottom, 0, QEnvironementInstance->width());
    ui->environementPlot->setAxisScale(QwtPlot::yLeft, 0, QEnvironementInstance->width());

    connect(tableList()->selectionModel(), &QItemSelectionModel::currentChanged, [&](const QModelIndex& current, const QModelIndex& previous){
        Q_UNUSED(previous);
        ui->upButton->setEnabled(current.isValid());
        ui->downButton->setEnabled(current.isValid());
    });

    connect(ui->heightValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setHeight(value);
        ui->zValue->setMaximum(value);
    });

    connect(ui->widthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setWidth(value);
        ui->xValue->setMaximum(value);
        ui->environementPlot->setAxisScale(QwtPlot::xBottom, 0, value);
    });

    connect(ui->lengthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironementInstance->setLength(value);
        ui->yValue->setMaximum(value);
        ui->environementPlot->setAxisScale(QwtPlot::yLeft, 0, value);
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
        filterModel()->invalidate();
        ui->beaconName->clear();
        ui->xValue->setValue(0);
        ui->yValue->setValue(0);
        ui->zValue->setValue(0);
        ui->beaconName->setFocus();
        repaintEnvironement();
    });
}

void QEnvironementEditor::repaintEnvironement() {
    const int N = QEnvironementInstance->beaconsCount();
    QVector<double> x(N, 0);
    QVector<double> y(N, 0);
    QPolygonF points;
    for (int i=0; i<N; i++) {
        const QBeacon beacon = QEnvironementInstance->beaconAt(i);
        const Position point = beacon->position();
        x[i] = point(0);
        y[i] = point(1);
    }
    _dataPlot->setSamples(x, y);
    ui->environementPlot->replot();
}

QEnvironementEditor::~QEnvironementEditor() {
    delete _sourceModel;
    delete _filterModel;
    delete ui;
}


QTableView* QEnvironementEditor::tableList() const {
    return ui->beaconList;
}

