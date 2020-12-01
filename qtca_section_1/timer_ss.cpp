#include "timer_ss.h"

Timer_SS::Timer_SS(QObject *parent) : QObject(parent)
{

}

void Timer_SS::setinterval(int value)
{
    this->interval = value;
}

void Timer_SS::started()
{
    qInfo() << "Timer started on " << QThread::currentThread();
    this->thread()->msleep(interval);
    emit timeout();
}
