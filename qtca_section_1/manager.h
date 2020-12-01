#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QWidget>
#include <QThread>
#include <QDebug>
#include <QList>
#include "counter.h"

class Manager : public QObject
{
    Q_OBJECT
public:
    explicit Manager(QObject *parent = nullptr);
    void start();

signals:

public slots:
    void started();
    void finished();

private:
    /* List of pointers to QThread objects */
    QList<QThread*> threads;

};

#endif // MANAGER_H
