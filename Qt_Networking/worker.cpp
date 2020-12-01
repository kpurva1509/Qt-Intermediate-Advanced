#include "worker.h"

// QMetaObject::Connection QObject::connect(
// const QObject *sender,
// const char *signal,
// const QObject *receiver,
// const char *method, // slots, connecting to sender's signals
// Qt::ConnectionType type = Qt::AutoConnection)

Worker::Worker(QObject *parent) : QObject(parent)
{
    /* connect the timer and socket variables to the worker */
    connect(&timer, &QTimer::timeout, this, &Worker::timeout);
    connect(&socket, &QUdpSocket::readyRead, this, &Worker::readyRead);
    timer.setInterval(1000);
}

void Worker::start()
{
    if(!socket.bind(port)) {
        qInfo() << socket.errorString();
        return;
    }
    qInfo() << "Started UDP connection on " <<
               socket.localAddress() << ": " << socket.localPort();
    readyBroadcast();

}

void Worker::stop()
{
    timer.stop();
    socket.close();
    qInfo() << "Stopped";
}

void Worker::timeout()
{
    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();

    /* UDP(User Defined Protocol) Specific Protocol */
    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);

   qInfo() << "Send: " << data;
   socket.writeDatagram(datagram);

}

void Worker::readyRead()
{
    while(socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "Read: " << datagram.data();
    }
}

void Worker::readyBroadcast()
{
    qInfo() << "Broadcasting...";
    timer.start();

}
