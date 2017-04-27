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


    connect(ui->addButton, &QToolButton::released, [&]() {
        const QString name = ui->beaconName->text();
        if (name.isEmpty()) {
            QMessageBox::information(this, "Empty name", "Please insert a valid name for the beacon");
            return;
        }

        const QBeacon beacon = QEnvironement::instance()->addBeacon();
        beacon->setName(name);
        filterModel()->invalidate();
        ui->beaconName->clear();
        ui->beaconPosition->clear();
        ui->beaconName->setFocus();
    });

    connect(tableList()->selectionModel(), &QItemSelectionModel::currentChanged, [&](const QModelIndex& current, const QModelIndex& previous){
        Q_UNUSED(previous);
        ui->upButton->setEnabled(current.isValid());
        ui->downButton->setEnabled(current.isValid());
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

