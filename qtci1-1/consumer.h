#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include "test4.h"
#include <QSharedDataPointer>

class Consumer : public QObject
{
    Q_OBJECT
public:
    explicit Consumer(QObject *parent = nullptr);
    ~Consumer();

    QSharedPointer<test4> tester;

signals:

};

#endif // CONSUMER_H
