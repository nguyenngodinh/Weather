#ifndef WEATHERBALLOON_H
#define WEATHERBALLOON_H

#include <QPushButton>
#include <QUdpSocket>
#include <QTimer>

class WeatherBalloon : public QPushButton
{
    Q_OBJECT
public:
    WeatherBalloon(QWidget* parent=0);
    QString temp() const;
    void sendDatagram();
private slots:
    void onReadyReadData();
private:
    bool mIsReceivePort;
    QHostAddress mDataHost;
    quint16 mDataPort;
    QUdpSocket udpSocket;
    QTimer timer;
};

#endif // WEATHERBALLOON_H
