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

    qDebug() << QEnvironement::instance()->width()
             << QEnvironement::instance()->length()
             << QEnvironement::instance()->height();

    ui->widthValue->setValue(QEnvironement::instance()->width());
    ui->lengthValue->setValue(QEnvironement::instance()->length());
    ui->heightValue->setValue(QEnvironement::instance()->height());


    connect(ui->addButton, &QToolButton::released, [&]() {
        const QString name = ui->beaconName->text();
        if (name.isEmpty()) {
            QMessageBox::information(this, "Empty name", "Please insert a valid name for the beacon");
            return;
        }

        const QBeacon beacon = QEnvironement::instance()->addBeacon();
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
    });

    connect(tableList()->selectionModel(), &QItemSelectionModel::currentChanged, [&](const QModelIndex& current, const QModelIndex& previous){
        Q_UNUSED(previous);
        ui->upButton->setEnabled(current.isValid());
        ui->downButton->setEnabled(current.isValid());
    });

    connect(ui->heightValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironement::instance()->setHeight(value);
        ui->zValue->setMaximum(value);
    });

    connect(ui->widthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironement::instance()->setWidth(value);
        ui->xValue->setMaximum(value);
    });

    connect(ui->lengthValue, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), [&](double value){
        QEnvironement::instance()->setLength(value);
        ui->yValue->setMaximum(value);
    });
}

QEnvironementEditor::~QEnvironementEditor() {
    delete ui;
    delete _sourceModel;
    delete _filterModel;
}


QTableView* QEnvironementEditor::tableList() const {
    return ui->beaconList;
}

