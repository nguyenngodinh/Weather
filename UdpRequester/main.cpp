#include <iostream>
#include <QCoreApplication>
#include <QUdpSocket>
#include <QThread>

#include <requester.h>
using namespace std;

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Hello World!" << endl;
//    QThread *thread = new QThread();
    Requester* requester = new Requester(3311);
//    QObject::connect(&requester->mSocket,SIGNAL(readyRead()), requester, SLOT(onReadyReadData()));
    requester->requestConnect(QString("192.168.1.95"), 3310);
//    requester->moveToThread(thread);
//    thread->start();

    return a.exec();
}

