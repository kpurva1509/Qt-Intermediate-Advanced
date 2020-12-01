#ifndef TIMER_SS_H
#define TIMER_SS_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QMutex>

class Timer_SS : public QObject
{
    Q_OBJECT
public:
    explicit Timer_SS(QObject *parent = nullptr);
    void setinterval(int value);

signals:
    void timeout();

public slots:
    void started();

private:
    int interval= 1000;

};

#endif // TIMER_SS_H
