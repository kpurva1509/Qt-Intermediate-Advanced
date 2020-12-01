#include "new_server.h"

new_server::new_server(QObject *parent) : QTcpServer(parent)
{
    pool.setMaxThreadCount(200);
    qInfo() << "Threads: " << pool.maxThreadCount();
}

void new_server::start(quint16 port)
{
    qInfo() << this << " start " << QThread::currentThread();
    if(this->listen(QHostAddress::Any, port))
    {
        qInfo() << "Server started on " << port;
    }
    else
    {
        qCritical() << this->errorString();
    }
}

void new_server::quit()
{
    this->close();
    qInfo() << "Server Stopped!";
}

void new_server::incomingConnection(qintptr handle)
{
    //Not Version friendly!!!
    qInfo() << "Incomming Connection " << handle << " on " << QThread::currentThread();
    new_client* client = new new_client(nullptr, handle);
    client->setAutoDelete(true);
    pool.start(client);

}
