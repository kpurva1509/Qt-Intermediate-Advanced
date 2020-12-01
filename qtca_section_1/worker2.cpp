#include "worker2.h"

Worker2::Worker2(QObject *parent, QStringList* data, QSemaphore* semaphore, int position) : QObject(parent), QRunnable()
{
    this->data = data;
    this->semaphore = semaphore;
    this->position = position;
}

void Worker2::run() {

    if(!data || !semaphore) {
        qInfo() << "Missing pointers";
        return;
    }

    /* Get the position, the data, and replace
     * with new data
     */
    QString string;
    string.sprintf("%08p", QThread::currentThread());
    semaphore->acquire(1);data->replace(position, QString::number(position)+" - "+ string);
    semaphore->release();

    qInfo() << string << " finished" << position;

}
