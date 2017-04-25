#ifndef QENVIRONEMENTEDITOR_H
#define QENVIRONEMENTEDITOR_H

#include "beaconfiltermodel.h"
#include "beaconlistmodel.h"

#include <QDialog>

namespace Ui {
class QEnvironementEditor;
}

class QEnvironementEditor : public QDialog
{
    Q_OBJECT

public:
    explicit QEnvironementEditor(QWidget *parent = 0);
    enum Steps { EnvironementEditor = 0, BeaconsEditor };
    ~QEnvironementEditor();
public slots:
    void setCurrentStep(Steps step);
private:
    Ui::QEnvironementEditor *ui;

    BeaconListModel*    _sourceModel;
    BeaconFilterModel*  _filterModel;
};

#endif // QENVIRONEMENTEDITOR_H
