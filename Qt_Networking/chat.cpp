#include "chat.h"

// QMetaObject::Connection QObject::connect(
// const QObject *sender,
// const char *signal,
// const QObject *receiver,
// const char *method, // slots, connecting to sender's signals
// Qt::ConnectionType type = Qt::AutoConnection)

chat::chat(QObject *parent) : QObject(parent)
{
    /* ShareAddress: multiple versions of this program
     * to talk on this address
     */
    if(!socket.bind(port, QUdpSocket::ShareAddress)) {
        qInfo() << socket.errorString();
    } else {
        qInfo() << "Started on " << socket.localAddress() << ": " << socket.localPort();
        connect(&socket, &QUdpSocket::readyRead, this, &chat::readyRead);
    }
}

void chat::command(QString value)
{
    QString message = name+": ";
    if(name.isEmpty()) {
        name = value;
        qInfo() << name << " just joined";
        send(message);
        return;
    }
    message.append(value);
    send(message);
}

void chat::send(QString message)
{
    QByteArray data = message.toLatin1();
    QNetworkDatagram datagram(data, QHostAddress::Broadcast, port);
    if(!socket.writeDatagram(datagram)) {
        qInfo() << socket.errorString();
    }
}

void chat::readyRead()
{
    while(socket.hasPendingDatagrams()) {
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo() << "Read: " << datagram.data();
    }

}
