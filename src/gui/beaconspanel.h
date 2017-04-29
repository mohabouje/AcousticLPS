#ifndef BEACONSPANEL_H
#define BEACONSPANEL_H

#include <model/qbeacon.h>
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
    inline BeaconListModel*   sourceModel() const { return _sourceModel; }
    inline BeaconFilterModel* filterModel() const { return _filterModel; }
public slots:
    void invalidate();
    void showHeader(bool show);
signals:
    void beaconEdited(const QBeacon &beacon);
    void beaconSelected(const QBeacon& beacon);
private:
    Ui::BeaconsPanel *ui;
    BeaconListModel*    _sourceModel;
    BeaconFilterModel*  _filterModel;
};

#endif // BEACONSPANEL_H
