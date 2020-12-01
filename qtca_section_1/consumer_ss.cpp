#include "consumer_ss.h"

Consumer_SS::Consumer_SS(QObject *parent) : QObject(parent)
{
    qInfo() << "Thread created on " << QThread::currentThread();
    thread.setObjectName("Timer Thread");
    /*
     * Qt::AutoConnection - runs on both
     * Qt::QueuedConnection - runs on main thread
     * Qt::DirectConnection - runs on thread
     * Qt::BlockingQueuedConnection - blocks
     * Qt::UniqueConnection - combined with others
     */
    connect(&timer, &Timer_SS::timeout,this, &Consumer_SS::timeout,Qt::QueuedConnection);
    connect(&thread, &QThread::started,&timer, &Timer_SS::started,Qt::QueuedConnection);
    connect(&thread, &QThread::finished,this, &Consumer_SS::finished,Qt::QueuedConnection);
}

void Consumer_SS::timeout()
{
    qInfo() << "Consumer thread timeout @ " << QThread::currentThread();
    thread.quit();
}

void Consumer_SS::start()
{
    qInfo() << "Consumer started on " << QThread::currentThread();
    timer.setinterval(500);
    timer.moveToThread(&thread);
    thread.start();
}

void Consumer_SS::finished()
{
    qInfo() << "Consumer thread finished @ " << QThread::currentThread();
}
