#include <QCoreApplication>
#include <QDebug>
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QAbstractSocket>
#include <QUdpSocket>
#include <QTcpSocket>
#include <QFuture>
#include <QNetworkProxy>
#include <QAuthenticator>
#include <QNetworkAccessManager>
#include <QSslSocket>
#include <QSslCertificate>
#include <QSslCertificateExtension>

/* User-defined classes */
#include "worker.h"
#include "commandline.h"
#include "chat.h"
#include "client.h"

bool bind(QUdpSocket* socket, quint16 port)
{
    if(socket->bind(port, QUdpSocket::ShareAddress)) return true;

    qInfo() << socket->errorString();
    return false;
}

void send(QUdpSocket* socket, quint16 port)
{
    qInfo() << "Sending...";
    QString date = QDateTime::currentDateTime().toString();
    QByteArray data = date.toLatin1();

    QNetworkDatagram datagram(data,QHostAddress::Broadcast,port); //network
    if(socket->writeDatagram(datagram) <= 0)
    {
        qInfo() << socket->errorString();
    }
}

void read(QUdpSocket* socket)
{
    qInfo() << "Reading...";
    socket->waitForReadyRead(60000);
    while (socket->hasPendingDatagrams())
    {
        QNetworkDatagram datagram = socket->receiveDatagram();
        qInfo() << datagram.data();
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* Lecture - 21(QHostAddress) */

    /* allAddresses() will combine the multiple interfaces for multiple
     * network cards in the connection into a single list
     */
    QList<QHostAddress> host_list = QNetworkInterface::allAddresses();

    for(int i=0; i< host_list.count(); i++) {

        QHostAddress address = host_list.at(i);
        qInfo() << address.toString();
        qInfo() << "\tLoopback: " << address.isLoopback();
        qInfo() << "\tMulticast: " << address.isMulticast();

        switch(address.protocol()) {
            case QAbstractSocket::UnknownNetworkLayerProtocol:
                qInfo() << "\t Protocol: Unknown";
                break;
            case QAbstractSocket::AnyIPProtocol:
                qInfo() << "\t Protocol: Random";
                break;
            case QAbstractSocket::IPv4Protocol:
                qInfo() << "\t Protocol: IPv4";
                break;
            case QAbstractSocket::IPv6Protocol:
                qInfo() << "\t Protocol: IPv6";
                break;
            default:
                qInfo() << "Defaulted";
                break;
        }
    }

    /* Lecture - 22(QUdpSocket) */

    Worker worker;
    // worker.start();

    /* Lecture - 23(UDP Chat Example) */

    commandline cli(&a, stdin);
    QFuture<void> future = QtConcurrent::run(&cli, &commandline::monitor);

    chat chat;
    QObject::connect(&cli, &commandline::command, &chat, &chat::command, Qt::QueuedConnection);

    qInfo() << "Enter your name to begin: ";

    /* Lecture - 24(QTcpSocket) */
    /* TCP Client2Website */

    Client client;
    client.connectToHost("www.voidrealms.com",80);

    /* Lecture - 25(QNetworkProxy) */

    Client client2;
    client2.connectToHost("httpbin.org", 80);

    /* Lecture - 26(QsslSocket - for secured connection) */

    Client client3;
    client3.connectToHost("httpbin.org", 443);

    /* Lecture - 27(Synchronous TCP) */

    QTcpSocket socket;
    socket.connectToHost("voidrealms.com",80);
    qInfo() << "Connecting...";
    if(socket.waitForConnected(60000))
    {
        qInfo() << "Connected sending request";

        QByteArray data;
        data.append("GET /get HTTP/1.1\r\n");
        data.append("Host: local\r\n");
        data.append("Connection: Close\r\n");
        data.append("\r\n");

        socket.write(data);
        socket.waitForBytesWritten();

        if(socket.waitForReadyRead(60000))
        {
            QByteArray response = socket.readAll();
            qInfo() << "Response: " << response.length() << "bytes";
            qInfo() << "Response: " << response;
        }

        //socket.close(); //we asked the server to close the connection
        socket.waitForDisconnected();
        qInfo() << "Done!";

    }
    else
    {
        qInfo() << socket.errorString();
    }

    /* Lecture - 28(Synchronous UDP) */

    QUdpSocket broadcaster;
    QUdpSocket new_client;
    quint16 port = 2020;

    qInfo() << "Binding...";

    if(bind(&broadcaster,port) && bind(&new_client,port))
    {
        send(&broadcaster,port);
        read(&new_client);
    }
    else
    {
        qInfo() << "Could not bind!";
    }

    /* Lecture - 29(QNetworkAccessManager) */




    return a.exec();
}
