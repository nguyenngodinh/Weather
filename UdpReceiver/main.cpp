#include <iostream>
#include <QCoreApplication>
#include <QThread>

#include <receiver.h>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cout << "Hello World!" << endl;

//    QThread *thread = new QThread();
    Receiver * receiver = new Receiver(3310, 3319);
//    QObject::connect(&receiver->mConnSocket, SIGNAL(readyRead()), receiver, SLOT(onReadyReadConn()));
//    QObject::connect(&receiver->mDataSocket, SIGNAL(readyRead()), receiver, SLOT(onReadyReadData()));
//    receiver->moveToThread(thread);
//    thread->start();

    return a.exec();
}

