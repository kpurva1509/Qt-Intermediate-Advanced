#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QRandomGenerator>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = nullptr);

signals:

public slots:
    void start();

protected:

};

#endif // COUNTER_H
