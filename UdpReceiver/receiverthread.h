#ifndef RECEIVERTHREAD_H
#define RECEIVERTHREAD_H

#include <QThread>

class ReceiverThread : public QThread
{
    Q_OBJECT
public:
    explicit ReceiverThread();
};

#endif // RECEIVERTHREAD_H
