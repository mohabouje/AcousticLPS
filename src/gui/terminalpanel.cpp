#include "terminalpanel.h"
#include "ui_terminalpanel.h"

TerminalPanel::TerminalPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TerminalPanel)
{
    ui->setupUi(this);
}

TerminalPanel::~TerminalPanel()
{
    delete ui;
}
