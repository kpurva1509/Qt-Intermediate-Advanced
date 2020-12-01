#include "consumer_wait.h"

Consumer_Wait::Consumer_Wait(QObject *parent) : QObject(parent)
{

}

void Consumer_Wait::setData(QList<int> *list)
{
    this->data = list;
}

void Consumer_Wait::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Consumer_Wait::setCondition(QWaitCondition *condition)
{
    this->condition = condition;
}

void Consumer_Wait::start()
{
    qInfo() << "Starting consumer on " << this->thread();

    do{
        mutex->lock();
        data->clear();
        // pause
        condition->wait(mutex);

        mutex->unlock();
    }while(true);

}
