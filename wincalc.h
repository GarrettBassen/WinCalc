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

private slots:
    void operand_pressed();
    void operator_pressed();
    void action_pressed();
    void calculate();
};
#endif // WINCALC_H
