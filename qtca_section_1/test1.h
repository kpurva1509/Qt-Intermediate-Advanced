#ifndef TEST1_H
#define TEST1_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QThreadPool>
#include <QThreadStorage>
#include <QDateTime>

class Test1 : public QObject
{
    Q_OBJECT
public:
    explicit Test1(QObject *parent = nullptr);

signals:

public slots:
    void timeout();
    void start();

private:
    QTimer timer;

};

#endif // TEST1_H
