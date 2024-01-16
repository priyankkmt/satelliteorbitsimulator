#include "stdafx.h"
#include <QtWidgets/QApplication>
#include "Simulator.h"

int main(int argc, char *argv[]) // start of the program
{
    // Initaite Application object and show simulator window
    QApplication applicationObj(argc, argv);
    Simulator simulatorObj;
    simulatorObj.show();
    return applicationObj.exec();
}