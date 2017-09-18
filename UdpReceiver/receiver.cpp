#include <QDataStream>
#include "receiver.h"
#include <unistd.h>

Receiver::Receiver(quint16 connPort, quint16 dataPort, QObject *parent)
    :QObject(parent)
{
    mConnPort = connPort;
    mDataPort = dataPort;
    bool isOk = mConnSocket.bind(QHostAddress("192.168.1.95"), connPort);
    QString connState = isOk?QString("conn socket bound to port %1").arg(connPort)
                           :QString("conn unsuccessfully bound to port %1").arg(connPort);
    connect(&mConnSocket, SIGNAL(readyRead()), this, SLOT(onReadyReadConn()));
    isOk = mDataSocket.bind(QHostAddress("192.168.1.95"), dataPort);
    QString dataState = isOk?QString("data socket bound to port %1").arg(connPort)
                           :QString("data unsuccessfully bound to port %1").arg(connPort);
    connect(&mDataSocket, SIGNAL(readyRead()), this, SLOT(onReadyReadData()));

    qDebug() << connState;
    qDebug() << dataState;
}

void Receiver::onReadyReadConn()
{
    while(mConnSocket.hasPendingDatagrams())
    {
        qDebug() << "read data!";
        QByteArray datagram;
        datagram.resize(mConnSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mConnSocket.readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);


        sleep(2);
        QByteArray msg;
        msg.append(QString("reciver msg firstly"));
        mDataSocket.writeDatagram(msg, msg.size(), sender, senderPort);
    }
}

void Receiver::onReadyReadData()
{
    while(mDataSocket.hasPendingDatagrams())
    {
        qDebug() << "read data!";
        QByteArray datagram;
        datagram.resize(mDataSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        mDataSocket.readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);
        QDataStream in(&datagram, QIODevice::ReadOnly);
        QString msg;
        in >> msg;
        qDebug() << "Receiver receive: " << msg;

        sleep(2);
        QByteArray msg_;
        QDataStream out(&msg_, QIODevice::WriteOnly);
        out << QString("msg from receiver");
        mDataSocket.writeDatagram(msg_, msg_.size(), sender, senderPort);
    }
}
