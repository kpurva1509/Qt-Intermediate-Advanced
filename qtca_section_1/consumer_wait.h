#ifndef CONSUMER_WAIT_H
#define CONSUMER_WAIT_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QThreadPool>
#include <QSemaphore>
#include <QRandomGenerator>
#include <QWaitCondition>

class Consumer_Wait : public QObject
{
    Q_OBJECT
public:
    explicit Consumer_Wait(QObject *parent = nullptr);
    /* pointer to a buffer provided */
    void setData(QList<int>* list);
    void setMutex(QMutex* mutex);
    void setCondition(QWaitCondition* condition);

public slots:
    void start();

private:
    QList<int>* data;
    QMutex* mutex;
    QWaitCondition* condition;
};

#endif // CONSUMER_WAIT_H
