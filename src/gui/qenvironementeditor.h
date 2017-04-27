#ifndef QENVIRONEMENTEDITOR_H
#define QENVIRONEMENTEDITOR_H

#include "beaconfiltermodel.h"
#include "beaconlistmodel.h"

#include <QDialog>
#include <qtableview.h>

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

    inline BeaconListModel* sourceModel() const { return _sourceModel; }
    inline BeaconFilterModel* filterModel() const { return _filterModel; }
    QTableView *tableList() const;
};


#endif // QENVIRONEMENTEDITOR_H
