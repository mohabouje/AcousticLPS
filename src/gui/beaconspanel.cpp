#include "beaconspanel.h"
#include "qenvironementeditor.h"
#include "ui_beaconspanel.h"

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
    ui->tableView->setShowGrid(false);
    connect(ui->editBeacons, &QToolButton::released, [&](){
        QEnvironementEditor dialog;
        dialog.setCurrentStep(QEnvironementEditor::BeaconsEditor);
        dialog.exec();
        _filterModel->invalidate();
    });
}

BeaconsPanel::~BeaconsPanel()
{
    delete ui;
    delete _sourceModel;
    delete _filterModel;
}
