#include "wincalc.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinCalc w;
    w.show();
    return a.exec();
}
