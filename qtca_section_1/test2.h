#ifndef TEST2_H
#define TEST2_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QThread>
#include <QThreadPool>
#include <QThreadStorage>
#include <QDateTime>

class Test2 : public QThread
{
    Q_OBJECT
public:
    explicit Test2(QObject *parent = nullptr);

signals:

public slots:
    void quit();

protected:
    void run();

private:
    bool ok;

};

#endif // TEST2_H
