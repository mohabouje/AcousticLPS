#ifndef BEACONSPANEL_H
#define BEACONSPANEL_H

#include <QWidget>

namespace Ui {
class BeaconsPanel;
}

class BeaconsPanel : public QWidget
{
    Q_OBJECT

public:
    explicit BeaconsPanel(QWidget *parent = 0);
    ~BeaconsPanel();

private:
    Ui::BeaconsPanel *ui;
};

#endif // BEACONSPANEL_H
