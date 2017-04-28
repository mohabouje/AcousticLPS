#ifndef QENVIRONEMENTEDITOR_H
#define QENVIRONEMENTEDITOR_H

#include "beaconfiltermodel.h"
#include "beaconlistmodel.h"

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <QDialog>
#include <QTableView>

namespace Ui {
class QEnvironementEditor;
}

class QEnvironementEditor : public QDialog
{
    Q_OBJECT

public:
    explicit QEnvironementEditor(QWidget *parent = 0);
    ~QEnvironementEditor();
private:
    Ui::QEnvironementEditor *ui;

    BeaconListModel*    _sourceModel;
    BeaconFilterModel*  _filterModel;
    QwtPlotCurve*       _dataPlot{new QwtPlotCurve("Beacons")};
    QwtSymbol*          _dataSymbol{new QwtSymbol()};
    inline BeaconListModel* sourceModel() const { return _sourceModel; }
    inline BeaconFilterModel* filterModel() const { return _filterModel; }
    QTableView *tableList() const;

    void initUi();
    void repaintEnvironement();
};


#endif // QENVIRONEMENTEDITOR_H
