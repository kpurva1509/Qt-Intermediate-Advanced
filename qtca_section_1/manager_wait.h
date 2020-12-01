#ifndef MANAGER_WAIT_H
#define MANAGER_WAIT_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QThreadPool>
#include <QSemaphore>
#include <QRandomGenerator>
#include <QWaitCondition>
#include "producer_wait.h"
#include "consumer_wait.h"

class Manager_Wait : public QObject
{
    Q_OBJECT
public:
    explicit Manager_Wait(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void ready();

private:
    QList<int> data;
    QMutex mutex;
    QThread producerThread;
    QThread consumerThread;
    QWaitCondition condition;
    Producer_Wait producer;
    Consumer_Wait consumer;


};

#endif // MANAGER_WAIT_H
