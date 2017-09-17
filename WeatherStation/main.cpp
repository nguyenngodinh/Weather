#include "mainwindow.h"
#include <QApplication>
#include "weatherstation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    WeatherStation station;
    station.show();

    return a.exec();
}
