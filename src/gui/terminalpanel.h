#ifndef TERMINALPANEL_H
#define TERMINALPANEL_H

#include <QWidget>

namespace Ui {
class TerminalPanel;
}

class TerminalPanel : public QWidget
{
    Q_OBJECT

public:
    explicit TerminalPanel(QWidget *parent = 0);
    ~TerminalPanel();

private:
    Ui::TerminalPanel *ui;
};

#endif // TERMINALPANEL_H
