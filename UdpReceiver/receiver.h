#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QUdpSocket>

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(quint16 connPort, quint16 dataPort, QObject* parent=0);
public slots:
    void onReadyReadConn();
    void onReadyReadData();
public:

    QUdpSocket mConnSocket;
    QUdpSocket mDataSocket;
    quint16 mConnPort;
    quint16 mDataPort;
};

#endif // RECEIVER_H
