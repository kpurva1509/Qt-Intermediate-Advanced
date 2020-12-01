#include "test1.h"

Test1::Test1(QObject *parent) : QObject(parent)
{

}

void Test1::timeout()
{
    qInfo() << "Before " << QDateTime::currentDateTime().toString()
            << " on " << QThread::currentThread();
}

void Test1::start()
{
    connect(&timer, &QTimer::timeout, this, &Test1::timeout);
    timer.setInterval(1000);
    timer.start();
}
