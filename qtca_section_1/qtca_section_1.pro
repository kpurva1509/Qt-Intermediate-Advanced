QT -= gui
QT += concurrent

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        consumer_ss.cpp \
        consumer_wait.cpp \
        counter.cpp \
        counter2.cpp \
        counter3.cpp \
        main.cpp \
        manager.cpp \
        manager_wait.cpp \
        producer_wait.cpp \
        test.cpp \
        test1.cpp \
        test2.cpp \
        timer_ss.cpp \
        worker.cpp \
        worker2.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    consumer_ss.h \
    consumer_wait.h \
    counter.h \
    counter2.h \
    counter3.h \
    manager.h \
    manager_wait.h \
    producer_wait.h \
    test.h \
    test1.h \
    test2.h \
    timer_ss.h \
    worker.h \
    worker2.h

QT += widgets
