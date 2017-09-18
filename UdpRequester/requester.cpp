#include "requester.h"
#include <QDataStream>
#include <unistd.h>

Requester::Requester(quint16 port, QObject *parent)
    :QObject(parent)
{
    bool isOk = mSocket.bind(QHostAddress("192.168.1.95"), port);
    connect(&mSocket, SIGNAL(readyRead()), this, SLOT(onReadyReadData()));
    QString state = isOk?QString("socket bound to port %1").arg(port)
                       :QString("Faild socket bound to port %1").arg(port);
    qDebug() << state;
}

void Requester::requestConnect(QString host, quint16 port)
{
    QByteArray data;
    data.append(QString("hello from request!"));
    mSocket.writeDatagram(data.data(), data.size(), QHostAddress(host), port);
}

void Requester::onReadyReadData()
{
    while(mSocket.hasPendingDatagrams())
    {
        qDebug() << "read data!";
        QByteArray datagram;
        datagram.resize(mSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mSocket.readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);
        QDataStream in(&datagram, QIODevice::ReadOnly);
        QString str;
        in >> str;
        qDebug() << "requester receive: " << str;

        sleep(2);
        QByteArray msg;
        QDataStream out(&msg, QIODevice::WriteOnly);
        out << QString("msg from requester");
        mSocket.writeDatagram(msg, msg.size(), sender, senderPort);
    }
}
