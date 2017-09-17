#ifndef WEATHERSTATION_H
#define WEATHERSTATION_H

#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QUdpSocket>
#include <QString>

class WeatherStation : public QDialog
{
    Q_OBJECT
public:
    WeatherStation(QWidget* parent=0);
private slots:
    void processRequestConnection();
    void onReadyReadData();
private:
    QUdpSocket udpSocket;
    QUdpSocket dataSocket;

    QHostAddress mDataHost;
    quint16 mDataPort;

    QLabel *dateLabel;
    QLabel *timeLabel;
    QLabel *tempLabel;

    QLineEdit *dateLineEdit;
    QLineEdit *timeLineEdit;
    QLineEdit *tempLineEdit;
};

#endif // WEATHERSTATION_H
