#ifndef PRODUCER_WAIT_H
#define PRODUCER_WAIT_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QThread>
#include <QThreadPool>
#include <QSemaphore>
#include <QRandomGenerator>

class Producer_Wait : public QObject
{
    Q_OBJECT
public:

    explicit Producer_Wait(QObject *parent = nullptr);

    /* pointer to a buffer provided */
    void setData(QList<int>* list);
    void setMutex(QMutex* mutex);

signals:
    void ready();

public slots:
    void start();

private:
    QList<int>* data;
    QMutex* mutex;

};

#endif // PRODUCER_WAIT_H
