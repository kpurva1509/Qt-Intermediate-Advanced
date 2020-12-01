#include "producer_wait.h"

Producer_Wait::Producer_Wait(QObject *parent) : QObject(parent)
{

}

void Producer_Wait::setData(QList<int> *data)
{
    this->data = data;
}

void Producer_Wait::setMutex(QMutex *mutex)
{
    this->mutex = mutex;
}

void Producer_Wait::start()
{
    int value = QRandomGenerator::global()->bounded(1000);
    do {
        mutex->lock();
        data->append(value);
        if(data->length() >= 100) emit ready();
        mutex->unlock();
    }while(true);
}
