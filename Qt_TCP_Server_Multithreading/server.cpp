#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    /* connect to the newConnection of the TCP Server, so that the TCP Server
     * knows when a  new connection request is made
     */
    connect(&server, &QTcpServer::newConnection, this, &Server::newConnection);
}

void Server::start()
{
    /* Socket binding - listening for incoming connections */
    server.listen(QHostAddress::Any, 2020);
}

void Server::quit()
{
    server.close();
}

void Server::newConnection()
{
    QTcpSocket* socket = server.nextPendingConnection();
    connect(socket, &QTcpSocket::disconnected, this, &Server::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Server::readyRead);
    qInfo() << "Connected " << socket;
}

void Server::disconnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qInfo() << "Disconnected" << socket;
}

void Server::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    qInfo() << "readyRead " << socket;
    qInfo() << socket->readAll();
}
