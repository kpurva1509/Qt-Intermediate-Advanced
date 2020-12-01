#ifndef SERVER_H
#define SERVER_H

#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSslSocket>
#include <QThread>
#include <QThreadPool>
#include <QThreadStorage>
#include <QSemaphoreReleaser>
#include <QString>
#include <QList>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void quit();
    void newConnection();
    void disconnected();
    void readyRead();

private:
    QTcpServer server;


};

#endif // SERVER_H
