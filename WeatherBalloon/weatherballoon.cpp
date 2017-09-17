#include "weatherballoon.h"
#include <QTimer>
#include <QDateTime>
#include <iostream>
#include <QThread>

WeatherBalloon::WeatherBalloon(QWidget *parent)
    : QPushButton(tr("Quit"), parent)
{
    udpSocket.bind(7001);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(onReadyReadData()));
    mIsReceivePort =false;
    setWindowTitle(tr("Weather Balloon"));
}

QString WeatherBalloon::temp() const
{
    return "WeatherBalloon";
}

void WeatherBalloon::onReadyReadData()
{
    QHostAddress senderHost;
    quint16 senderPort;
    QByteArray datagram;
    do
    {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size(),
                               &senderHost, &senderPort);
    }while(udpSocket.hasPendingDatagrams());
    QDataStream in(&datagram, QIODevice::ReadOnly);
    if(mIsReceivePort)
    {
        QDateTime dateTime;
        QString msg;
        in >> dateTime >> msg;
        std::cout << "Ballon receive: msg[" << msg.toStdString() << "] at "
                  << dateTime.date().toString().toStdString() << ":"
                  << dateTime.time().toString().toStdString()
                  << " from " << senderHost.toString().toStdString() << ":" << senderPort << std::endl;
        QThread::sleep(5);

        QByteArray datagram_;
        QDataStream out(&datagram_, QIODevice::WriteOnly);
        out << QDateTime::currentDateTime() << QString("Weather Ballon");
        QUdpSocket socket;
        socket.writeDatagram(datagram_, mDataHost, mDataPort);

    }
    else
    {
        quint16 portInfo;
        in >> portInfo;
        mDataPort = portInfo;
        mDataHost = senderHost;
        mIsReceivePort = true;
        std::cout << "Port info: " << portInfo << std::endl;
    }
}

void WeatherBalloon::sendDatagram()
{
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    quint16 listenPortInfo = 7001;
    out << listenPortInfo;
    QUdpSocket socket;
    socket.writeDatagram(datagram, QHostAddress("192.168.1.95"), 7000);
}
