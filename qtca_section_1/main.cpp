#include <QCoreApplication>
#include <QDeadlineTimer>
#include <QDateTime>
#include <QDebug>
#include <QVariantMap>
#include <QMap>
#include <QList>
#include <QTimer>
#include <QVector>
#include <QFile>
#include <QFileInfo>
#include <QIODevice>
#include <QThread>
#include <QThreadPool>
#include <QThreadStorage>
#include <QSharedDataPointer>
#include <QSharedPointer>
#include <QMutex>
#include <QMutexLocker>
#include <QSemaphore>
#include <QWaitCondition>
#include <QtConcurrent/QtConcurrent>
#include <QFuture>
#include <QFutureWatcher>

#include "test1.h"
#include "test2.h"
#include "counter.h"
#include "manager.h"
#include "counter2.h"
#include "counter3.h"
#include "worker.h"
#include "worker2.h"
#include "producer_wait.h"
#include "consumer_wait.h"
#include "manager_wait.h"
#include "consumer_ss.h"
#include "timer_ss.h"
#include "test.h"

static QSharedPointer<QThread> sptr;
void timeout() {
    if(!sptr.isNull()) {
        qInfo() << "Stopping other thread from running";
        sptr.data()->quit();
    }
}

/* mapped function */
int do_map(int value) {

    qInfo() << "Do stuff";
    int num = value*10;
    return num;

}

void loop() {
    /* looping on a specific thread */
    for(int i=0; i<10; i++) {
        qInfo() << "Looping on " << QThread::currentThread();
    }
}

void test() {
    qInfo() << "Testing on " << QThread::currentThread();
    loop();
}

void test(QString name, int max) {
    for(int i=0; i<max; i++) {
        qInfo() << name << i <<  QThread::currentThread();
    }
}

void multiply(int&& value) {
    qInfo() << "Called";
    value = value*10;
}

int multiply2(int&& value) {
    qInfo() << "Called";
    int num = value+10;
    return num;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Section - 1, Lecture - 1(Exploring the current thread)

    qInfo() << "Application thread: " << a.thread();
    qInfo() << "Current thread: " << QThread::currentThread();
    Q_ASSERT(a.thread() == QThread::currentThread());

    qInfo() << "Running " << QThread::currentThread()->isRunning();
    qInfo() << "Looplevel " << QThread::currentThread()->loopLevel();
    qInfo() << "Stack size " << QThread::currentThread()->stackSize();
    qInfo() << "Running " << QThread::currentThread()->isFinished();

    qInfo() << "Before " << QDateTime::currentDateTime().toString();
    QThread::sleep(4);
    qInfo() << "After " << QDateTime::currentDateTime().toString();

    // Section - 1, Lecture - 2(Creating threads)

    qInfo() << "Application thread: " << a.thread();
    qInfo() << "Current thread: " << QThread::currentThread();
    Test1 test;
    qInfo() << "Timer thread: " << test.thread();

    /* Moving a thread to another thread, create another thread */
    /* Test class inherited from QObject, has thread pointer too */
    /* Cannot move objects with parent */
    QThread thread;
    sptr.reset(&thread);
    test.moveToThread(&thread);
    qInfo() << "Timer thread: " << test.thread();

    test.start();
    qInfo() << "Thread state: " << thread.isRunning();
    thread.start();

    QTimer timer;
    timer.singleShot(5000, &timeout);

    // Section - 1, Lecture - 3(Inherting QObject)

    Test2 custom_thread;
    sptr.reset(&custom_thread);
    custom_thread.start();

    QTimer my_timer;
    my_timer.singleShot(5000, &timeout);

    // Section - 1, Lecture - 4(Thread Lifecycle)

    /* Manager class is going to create multiple threads */
    /* Each thread will have an associated couter object with it */
    QThread::currentThread()->setObjectName("Main");
    Manager manager;
    manager.start();

    // Section - 1, Lecture - 5(Threadpools)

    QThread::currentThread()->setObjectName("main");
    /* Qt based application generates a threadpool in the
     * background on starting the application
     * Here, we get an instance of the already existing
     * threadpool
     */
    QThreadPool* pool = QThreadPool::globalInstance();

    /* Hardware concurrency on the system/platform */
    qInfo() << pool->maxThreadCount() << " Threads";

    for(int i=0; i<100; i++) {
        Counter2* my_counter = new Counter2;
        my_counter->setAutoDelete(true);
        pool->start(my_counter);
    }

    // Section - 1, Lecture - 6(QMutex)
    /* Contention, and deadlock contention, critical
     * section, so use mutex flags
     */

    // Section - 1, Lecture - 7(QMutexLocker)

    Counter3 counter;
    QMutex mutex(QMutex::Recursive);
    QThreadPool* my_pool = QThreadPool::globalInstance();

    qInfo() << "Count: " << counter.count();

    for(int i=0; i<my_pool->maxThreadCount(); i++) {
        Worker* worker = new Worker(&a, &counter, &mutex);
        worker->setAutoDelete(true);
        my_pool->start(worker);
    }
    my_pool->waitForDone();

    qInfo() << "Done, the count is " <<counter.count();

    // Section - 1, Lecture - 8(QSemaphore)

    QStringList data;

    for(int i=0; i<100; i++) {
        data.append(QString::number(i));
    }

    QThreadPool* my_pool_2 = QThreadPool::globalInstance();
    QSemaphore semaphore;

    for(int i=0; i<data.length(); i++) {
        Worker2* worker = new Worker2(&a, &data, &semaphore, i);
        worker->setAutoDelete(true);
        my_pool_2->start(worker);
    }

    my_pool_2->waitForDone();

    foreach(QString string, data) {
        qInfo() << string;
    }

    // Section - 1, Lecture - 9(QWaitCondition + Produced-Consumer Design)

    Manager_Wait manager_obj;
    manager_obj.start();

    // Section - 1, Lecture -10(Signals and slots in Threads)

    QThread::currentThread()->setObjectName("Main Thread");
    qInfo() << "Application started on " << QThread::currentThread();

    Consumer_SS consumer;
    consumer.start();

    /********************************************************************/

    // Section - 1, Lecture 11(Introduction to QtConcurrent)

    QList<int> values;
    for(int i=0; i<10; i++) {
        values << i;
    }

    qInfo() << "Starting blocked";
    QList<int> updated = QtConcurrent::blockingMapped(values, &do_map);

    qInfo() << updated;
    qInfo() << "Finished blocked";

    // Section - 1, Lecture 12(QtConcurrent - run)

    QThread::currentThread()->setObjectName("Main");

    QThreadPool new_pool;
    // QFuture<void> future = QtConcurrent::run(&new_pool,test);
    qInfo() << "Main on: " << QThread::currentThread();
    loop();

    // Section - 1, Lecture 13(QtConcurrent issues)

    QString name = "name";
    // QFuture<void> future = QtConcurrent::run(test,name,5);
    // QFuture<void> future = QtConcurrent::run(test, "name", 5);

    // Section - 1, Lecture - 13(QFutureWatcher)

    QList<int> list;

    for(int i=0; i<10; i++) {
        list.append(i);
    }

    QFutureWatcher<void> watcher;

    QFuture<void> future = QtConcurrent::map(list, &multiply);
    watcher.setFuture(future);

    watcher.waitForFinished();

    qInfo() << "Done";
    qInfo() << list;

    // Section - 1, Lecture - 14(QFuture getting values)

    QList<int> list2;
    for (int i = 0;i < 100; i++)
    {
        list2.append(i);
    }

    QFutureWatcher<int> watcher2;

    QFuture<int> future2 = QtConcurrent::mapped(list2,&multiply2);
    watcher2.setFuture(future2);
    qInfo() << "Back in main!";

    watcher2.waitForFinished();

    qInfo() << "Done!";
    qInfo() << future2.results();

    // Section - 1, Lecture - 15(QFutureWatcher slots)

    Test new_test;
    new_test.process();

    return a.exec();
}
