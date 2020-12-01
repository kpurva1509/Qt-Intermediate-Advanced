#ifndef COUNTER3_H
#define COUNTER3_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QRunnable>
#include <QThreadPool>
#include <QRandomGenerator>

class Counter3 : public QObject
{
    Q_OBJECT
public:
    explicit Counter3(QObject *parent = nullptr);
    void increment();
    void decrement();
    int count();

signals:

public slots:

private:
    int value;

};

#endif // COUNTER3_H
