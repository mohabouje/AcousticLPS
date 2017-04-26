#include "beaconspanel.h"
#include "helper.h"
#include "qenvironementeditor.h"
#include "ui_beaconspanel.h"

#include <QMenu>

BeaconsPanel::BeaconsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeaconsPanel),
    _sourceModel(new BeaconListModel(parent)),
    _filterModel(new BeaconFilterModel(parent))
{
    ui->setupUi(this);

    _filterModel->setSourceModel(_sourceModel);
    ui->tableView->setModel(_filterModel);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setShowGrid(false);

    connect(ui->editBeacons, &QToolButton::released, [&](){
        QEnvironementEditor dialog;
        dialog.setCurrentStep(QEnvironementEditor::BeaconsEditor);
        dialog.exec();
        _filterModel->invalidate();
    });

    connect(ui->tableView, &QTableView::customContextMenuRequested, [&](const QPoint& point) {
        const QModelIndex index = ui->tableView->indexAt(point);
        const QBeacon beacon = Gui::qBeaconFromQModelIndex(index);
        if (!beacon.isNull()) {
            QMenu menu;
            menu.addAction(beacon->isEnabled() ? tr("Disable") : tr("Enable"),[&, beacon](){
                const bool isEnabled = beacon->isEnabled();
                beacon->setEnabled(!isEnabled);
            });
            menu.exec(ui->tableView->viewport()->mapToGlobal(point));
        }
    });
}

BeaconsPanel::~BeaconsPanel()
{
    delete ui;
    delete _sourceModel;
    delete _filterModel;
}
