#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    connect(&socket, &QTcpSocket::connected, this, &Client::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &Client::disconnected);
    connect(&socket, &QTcpSocket::readyRead, this, &Client::readyRead);
    connect(&socket, &QTcpSocket::stateChanged, this, &Client::stateChanged);

    connect(&socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::error);

    QNetworkProxy proxy(QNetworkProxy::HttpProxy, "171.100.204.126", 50058);
    /* set authenticators
    proxy.setUser("username");
    proxy.setPassword("password");
    */
    socket.setProxy(proxy);

    /* connec to SSL signal slots */
    connect(&socket2, &QSslSocket::encrypted, this, &Client::encrypted);
    connect(&socket2, &QSslSocket::encryptedBytesWritten, this, &Client::encryptedBytesWritten);
    connect(&socket2, &QSslSocket::modeChanged, this, &Client::modeChanged);
    connect(&socket2, &QSslSocket::peerVerifyError, this, &Client::peerVerifyError);
    connect(&socket2, &QSslSocket::preSharedKeyAuthenticationRequired, this, &Client::preSharedKeyAuthenticatorRequired);
    connect(&socket2, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &Client::sslErrors);

}

void Client::connectToHost(QString host, quint16 port)
{
    /* virtual connection for the 3-way handshake */
    if(socket.isOpen()) disconnect();
    qInfo() << "Connecting to " << host << " on port " << port;

    /* unsecured TCP connection to host */
    socket.connectToHost(host, port);

    /* secured SSL connection to host */
    socket2.ignoreSslErrors();
    socket2.setProtocol(QSsl::AnyProtocol);
    socket2.connectToHostEncrypted(host, port);
}

void Client::disconnect()
{
    socket.close();
}

void Client::connected()
{
    qInfo() << "Connected";
    qInfo() << "Sending";
    // socket.write("hello\r\n");

    QByteArray data;
    data.append("GET /get HTTP/1.1\r\n");
    data.append("User-Agent: Mozilla/4.0 (compatible; MSIE 8.0; Windows NT 6.0; Trident/4.0)\r\n");
    data.append("Host: local\r\n");
    data.append("Connection: Close\r\n");
    data.append("\r\n");
    socket.write(data);
    socket.waitForBytesWritten();
}

void Client::disconnected()
{
    qInfo() << "Disconnected";

}

void Client::error(QAbstractSocket::SocketError socketError)
{
    qInfo() << "Error: " << socketError << " " << socket.errorString();
}

void Client::stateChanged(QAbstractSocket::SocketState socketState)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    /* char representation of socket */
    qInfo() << "State: " << metaEnum.valueToKey(socketState);
}

void Client::readyRead()
{
    qInfo() << "Data from " << sender() << " bytes: " << socket.bytesAvailable();
    qInfo() << "Data: " << socket.readAll();
}

void Client::encrypted()
{
    qInfo() << "Encrypted";
}

void Client::encryptedBytesWritten(qint64 written)
{
    qInfo() << "encryptedBytesWritten " << written;
}

void Client::modeChanged(QSslSocket::SslMode mode)
{
    qInfo() << "SslMode: " << mode;
}

void Client::peerVerifyError(const QSslError &error)
{
    qInfo() << "peerVerifyError: " << error.errorString();
}

void Client::preSharedKeyAuthenticatorRequired(QSslPreSharedKeyAuthenticator *authenticator)
{
    qInfo() << "Preshared key required";
}

void Client::sslErrors(const QList<QSslError> &errors)
{
    qInfo() << "SSL Errors";
    foreach(QSslError error, errors) {
        qInfo() << error.errorString();
    }
}
