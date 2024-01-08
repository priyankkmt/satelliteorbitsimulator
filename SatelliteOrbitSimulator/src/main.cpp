#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "Simulator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simulator w;
    w.show();
    return a.exec();
}