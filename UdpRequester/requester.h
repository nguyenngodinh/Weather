#ifndef REQUESTER_H
#define REQUESTER_H

#include <QObject>
#include <QUdpSocket>

class Requester : public QObject
{
    Q_OBJECT
public:
    explicit Requester(quint16 port, QObject* parent=0);
    void requestConnect(QString host, quint16 port);
public slots:
    void onReadyReadData();
public:
    QUdpSocket mSocket;
};

#endif // REQUESTER_H
