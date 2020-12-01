#ifndef CALL_ONCE_H
#define CALL_ONCE_H

#include <QDebug>
#include <QAtomicInt>
#include <QThread>
#include <QThreadPool>
#include <QThreadStorage>
#include <QGlobalStatic>
#include <QMutex>
#include <QWaitCondition>
#include <QtGlobal>

namespace call_once {
    enum e_call_once {
        CO_Request,
        CO_InProgress,
        CO_Finished
    };
    /* Thread-safe initialization of the global static object of class */
    Q_GLOBAL_STATIC(QThreadStorage<QAtomicInt*>, once_flag);
}

template<typename Function>
static inline void q_call_once(Function&& func, QBasicAtomicInt& flag) {

    using namespace call_once;

#if QT_VERSION < 0x050000
    int protected_flag = flag.fetchAndStoreAcquire(flag);
#elif QT_VERSION > 0x050000
    int protected_flag = flag.fetchAndStoreAcquire(flag.load());
#endif

    if(protected_flag == CO_Finished)
        return;
    if(protected_flag == CO_Request && flag.testAndSetRelaxed(protected_flag,CO_InProgress)) {
        func();
        flag.fetchAndStoreRelease(CO_Finished);
    } else {
        do{
            QThread::yieldCurrentThread();
        }while(!flag.testAndSetAcquire(CO_Finished, CO_Finished));
    }
}

template<typename Function>
static inline void q_call_once_per_thread(Function&& func) {

    using namespace call_once;
    if(!once_flag->hasLocalData()) {
        once_flag->setLocalData(new QAtomicInt(CO_Request));
        q_call_once(func, once_flag->hasLocalData());
    }
}

#endif // CALL_ONCE_H
