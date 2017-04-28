#include "beaconspanel.h"
#include "helper.h"
#include "qenvironementeditor.h"
#include "ui_beaconspanel.h"

#include <QMenu>

#include <model/qenvironement.h>

BeaconsPanel::BeaconsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeaconsPanel),
    _sourceModel(new BeaconListModel(parent)),
    _filterModel(new BeaconFilterModel(parent))
{
    ui->setupUi(this);

    filterModel()->setSourceModel(sourceModel());
    ui->tableView->setModel(filterModel());
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionsClickable(true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->tableView->setShowGrid(false);
    ui->tableView->setSortingEnabled(true);

    connect(ui->tableView, &QTableView::customContextMenuRequested, [&](const QPoint& point) {
        const QModelIndex index = ui->tableView->indexAt(point);
        const QBeacon beacon = Gui::qBeaconFromQModelIndex(index);
        if (!beacon.isNull()) {
            QMenu menu;
            menu.addAction(beacon->isEnabled() ? tr("Disable") : tr("Enable"),[&, beacon](){
                const bool isEnabled = beacon->isEnabled();
                beacon->setEnabled(!isEnabled);
                emit beaconEdited(beacon);
                filterModel()->invalidate();
            });
            menu.addAction(tr("Remove"), [&, beacon]() {
                QEnvironementInstance->removeBeacon(beacon);
                emit beaconEdited(beacon);
                filterModel()->invalidate();
            });
            menu.exec(ui->tableView->viewport()->mapToGlobal(point));
        }
    });

    connect(ui->tableView->horizontalHeader(), &QHeaderView::sectionClicked, [&](int section) {
        const BeaconFilterModel::SortType sort = static_cast<BeaconFilterModel::SortType>(section);
        filterModel()->setSort(sort);
    });
}

BeaconsPanel::~BeaconsPanel()
{
    delete ui;
    delete _sourceModel;
    delete _filterModel;
}

void BeaconsPanel::invalidate() {
    filterModel()->invalidate();
}
