#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QMetaEnum>
#include <QNetworkProxy>
#include <QSslSocket>
#include <QSslPreSharedKeyAuthenticator>


class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);

signals:

public slots:
    void connectToHost(QString host, quint16 port);
    void disconnect();

private slots:
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError socketError);
    void stateChanged(QAbstractSocket::SocketState socketState);
    void readyRead();

    /* Additional slots for SSL Connection */
    void encrypted();
    void encryptedBytesWritten(qint64 written);
    void modeChanged(QSslSocket::SslMode mode);
    void peerVerifyError(const QSslError& error);
    void preSharedKeyAuthenticatorRequired(QSslPreSharedKeyAuthenticator* authenticator);
    void sslErrors(const QList<QSslError>& errors);

private:
    QTcpSocket socket;
    QSslSocket socket2;
};

#endif // CLIENT_H
