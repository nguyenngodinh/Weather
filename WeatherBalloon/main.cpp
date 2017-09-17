#include "mainwindow.h"
#include <QApplication>
#include "weatherballoon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WeatherBalloon balloon;

    balloon.show();
    balloon.sendDatagram();

    return a.exec();
}
