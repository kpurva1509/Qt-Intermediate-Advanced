#ifndef WORKER2_H
#define WORKER2_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QIODevice>
#include <QRunnable>
#include <QThreadPool>
#include <QRandomGenerator>
#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>

class Worker2 : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Worker2(QObject *parent = nullptr, QStringList* data = nullptr, QSemaphore* semaphore = nullptr, int position = -1);
    void run();
signals:

public slots:

private:
    QStringList* data;
    QSemaphore* semaphore;
    int position;
};

#endif // WORKER2_H
