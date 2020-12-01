#include <QCoreApplication>
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

/* User-defined classes */
// #include "server.h"
#include "new_client.h"
#include "new_server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Server server;
    // server.start();

    /* Multithreaded TCP Server */

    new_server n_server;
    n_server.start(2000);

    return a.exec();
}
