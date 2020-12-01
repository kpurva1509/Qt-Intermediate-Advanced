#include "counter2.h"


void Counter2::run()
{
    for(int i=0; i<20; i++) {
        qInfo() << "Current thread:" << QThread::currentThread()->objectName() << " = " << i;
        auto value = static_cast<unsigned long>(QRandomGenerator::global()->bounded(500));
        QThread::currentThread()->msleep(value);
    }
    qInfo() << "Finished " << QThread::currentThread();
}
