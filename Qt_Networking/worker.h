#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QUdpSocket>
#include <QNetworkDatagram>

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = nullptr);

signals:

public slots:
    void start();
    void stop();
    void timeout();
    void readyRead();
    void readyBroadcast();

private:
    QUdpSocket socket;
    QTimer timer;

    /* port < 1024 are called Admin Ports or Special Services
     * - HTTP, FTP, POP3, SMTP */
    quint16 port = 2020;

};

#endif // WORKER_H
