#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QRunnable>
#include <QThreadPool>
#include <QRandomGenerator>
#include <QMutex>
#include <QMutexLocker>

#include "counter3.h"

class Worker : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr, Counter3* counter = nullptr, QMutex* mutex = nullptr);
    void run();
signals:

public slots:

private:
    Counter3* counter;
    QMutex*mutex;

};

#endif // WORKER_H
