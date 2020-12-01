#ifndef COUNTER2_H
#define COUNTER2_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QRunnable>
#include <QThreadPool>
#include <QRandomGenerator>

class Counter2 : public QRunnable
{

public:
    void run();

};

#endif // COUNTER2_H
