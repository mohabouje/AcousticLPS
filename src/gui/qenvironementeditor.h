#ifndef QENVIRONEMENTEDITOR_H
#define QENVIRONEMENTEDITOR_H

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
    void initUi();
};


#endif // QENVIRONEMENTEDITOR_H
