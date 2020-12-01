#include "manager_wait.h"

Manager_Wait::Manager_Wait(QObject *parent) : QObject(parent)
{
    connect(&producerThread,&QThread::started,&producer,&Producer_Wait::start, Qt::QueuedConnection);
    connect(&producer,&Producer_Wait::ready,this,&Manager_Wait::ready, Qt::QueuedConnection);
    connect(&consumerThread,&QThread::started,&consumer,&Consumer_Wait::start, Qt::QueuedConnection);

    producerThread.setObjectName("Producer Thread");
    consumerThread.setObjectName("Consumer Thread");
    this->thread()->setObjectName("Main Thread");

    producer.moveToThread(&producerThread);
    consumer.moveToThread(&consumerThread);
}

void Manager_Wait::start()
{
    producer.setMutex(&mutex);
    producer.setData(&data);

    consumer.setMutex(&mutex);
    consumer.setData(&data);
    consumer.setCondition(&condition);

    producerThread.start();
    consumerThread.start();

}

void Manager_Wait::ready()
{
    qInfo() << "Data is ready " << this->thread();
    condition.wakeAll();
}
