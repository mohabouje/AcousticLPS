#ifndef QENVIRONEMENTEDITOR_H
#define QENVIRONEMENTEDITOR_H


#include "beaconspanel.h"

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
private slots:
    void repaintEnvironement();
    void initUi();
private:
    Ui::QEnvironementEditor *ui;
    QwtPlotCurve*   _enabledBeacons{new QwtPlotCurve()};
    QwtPlotCurve*   _disabledBeacons{new QwtPlotCurve()};
    QwtSymbol*      _enabledSymbol{new QwtSymbol};
    QwtSymbol*      _disabledSymbol{new QwtSymbol};

    BeaconsPanel* beaconsPanel() const;
};


#endif // QENVIRONEMENTEDITOR_H
