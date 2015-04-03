#include <QCoreApplication>
#include <iostream>
#include "spaceprobe.h"

#include <QDebug>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SpaceProbe sp(20, 0, 0, 19, 0);
    sp.showSpace();
    if(sp.run()) {
        qDebug() << "================ Found path =================";
        sp.showSpace();
    }

    return a.exec();
}
