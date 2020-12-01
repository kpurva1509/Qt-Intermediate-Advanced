#include "worker.h"

Worker::Worker(QObject *parent, Counter3* counter, QMutex* mutex) : QObject(parent), QRunnable()
{
    this->counter = counter;
    this->mutex = mutex;
}

void Worker::run() {
    if(!counter) {
        return;
    }
    qInfo() << this << " started";

    for(int i=0; i<100; i++) {
        /* RAII wrapper around a raw mutex */
        QMutexLocker locker(mutex);
        counter->increment();
        qInfo() << this << " Count: " << counter->count();
        counter->decrement();
    }

    qInfo() << this << " finished";
}
