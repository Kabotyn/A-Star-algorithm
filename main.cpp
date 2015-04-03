#include <QCoreApplication>
#include <iostream>
#include "spaceprobe.h"

#include <QDebug>




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SpaceProbe sp(50, 0, 0, 49, 49);
    sp.showSpace();
    if(sp.run()) {
        qDebug() << "=================================";
        sp.showSpace();
    }

    return a.exec();
}
