#ifndef WINCALC_H
#define WINCALC_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class WinCalc;
}
QT_END_NAMESPACE

class WinCalc : public QMainWindow
{
    Q_OBJECT

public:
    WinCalc(QWidget *parent = nullptr);
    ~WinCalc();

private:
    Ui::WinCalc *ui;
    QList<double> memList;

private slots:
    void operand_pressed();
    void operator_pressed();
    void action_pressed();
    void calculate();
    void clear();
    void memory();

private:
    void set_display_small();
    void clear_triggers();
};
#endif // WINCALC_H
