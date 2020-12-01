#ifndef CONSUMER_SS_H
#define CONSUMER_SS_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include "timer_ss.h"

class Consumer_SS : public QObject
{
    Q_OBJECT
public:
    explicit Consumer_SS(QObject *parent = nullptr);

signals:

public slots:
    void timeout();
    void start();
    void finished();

private:
    QThread thread;
    Timer_SS timer;

};

#endif // CONSUMER_SS_H
