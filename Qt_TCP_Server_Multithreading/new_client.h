#ifndef NEW_CLIENT_H
#define NEW_CLIENT_H

#include <QObject>
#include <QThread>
#include <QRunnable>
#include <QTcpSocket>
#include <QTcpSocket>

class new_client : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit new_client(QObject *parent = nullptr, qintptr handle = 0);

signals:


    // QRunnable interface
public:
    void run();

private:
    qintptr handle;
};

#endif // NEW_CLIENT_H
