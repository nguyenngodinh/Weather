#include "weatherstation.h"
#include <QDialog>
#include <QDateTime>
#include <iostream>
#include <QHostAddress>
#include <QThread>

WeatherStation::WeatherStation(QWidget *parent)
    : QDialog(parent)
{
    udpSocket.bind(7000);
    dataSocket.bind(7007);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processRequestConnection()));
    connect(&dataSocket, SIGNAL(readyRead()), this, SLOT(onReadyReadData()));
}

void WeatherStation::processRequestConnection()
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
    quint16 portInfo;
    QDataStream in(&datagram, QIODevice::ReadOnly);
//    in.setVersion(QDataStream::Qt_4_3);
    in >> portInfo;
    std::cout << "portInfo: " << portInfo << " from host " << senderHost.toString().toStdString() << std::endl;
    mDataHost = senderHost;
    mDataPort = portInfo;

    QByteArray datagram2;
    QDataStream out(&datagram2, QIODevice::WriteOnly);
    quint16 dataPort = 7007;
    out << dataPort;
    QUdpSocket socket;
    socket.writeDatagram(datagram2, mDataHost, mDataPort);

    QThread::sleep(5);
    QByteArray datagram3;
    QDataStream out2(&datagram3, QIODevice::WriteOnly);
    out2 << QDateTime::currentDateTime() << "Weather Station";
    QUdpSocket socket2;
    socket2.writeDatagram(datagram3, mDataHost, mDataPort);
}

void WeatherStation::onReadyReadData()
{
    QHostAddress sender;
    quint16 port;
    QByteArray datagram_;
    QDateTime dateTime;
    QString msg;
    do{
        datagram_.resize(dataSocket.pendingDatagramSize());
        dataSocket.readDatagram(datagram_.data(), datagram_.size(), &sender, &port);
    }while(dataSocket.hasPendingDatagrams());
    QDataStream in(&datagram_, QIODevice::ReadOnly);
    in >> dateTime >> msg;
    std::cout << "Station receive: msg[" << msg.toStdString() << "] at "
              << dateTime.date().toString().toStdString() << ":"
              << dateTime.time().toString().toStdString()
              << " from " << sender.toString().toStdString() << ":" << port << std::endl;


    QThread::sleep(5);
    QByteArray datagram;
    QDataStream out(&datagram, QIODevice::WriteOnly);
    out << QDateTime::currentDateTime() << QString("Weather Station");
    QUdpSocket socket;
    socket.writeDatagram(datagram, mDataHost, mDataPort);
}
