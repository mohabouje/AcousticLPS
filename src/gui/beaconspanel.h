#ifndef BEACONSPANEL_H
#define BEACONSPANEL_H

#include "beaconfiltermodel.h"
#include "beaconlistmodel.h"

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
    BeaconListModel*    _sourceModel;
    BeaconFilterModel*  _filterModel;

    inline BeaconListModel*   sourceModel() const { return _sourceModel; }
    inline BeaconFilterModel* filterModel() const { return _filterModel; }
};

#endif // BEACONSPANEL_H
