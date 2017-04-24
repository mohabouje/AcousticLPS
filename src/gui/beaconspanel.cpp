#include "beaconspanel.h"
#include "ui_beaconspanel.h"

BeaconsPanel::BeaconsPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BeaconsPanel)
{
    ui->setupUi(this);
}

BeaconsPanel::~BeaconsPanel()
{
    delete ui;
}
