#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include "chatprotocol.h"

class ClientManager : public QObject
{
    Q_OBJECT
public:
    explicit ClientManager(QHostAddress ip = QHostAddress::LocalHost, ushort port = 4500, QObject *parent = nullptr);
    explicit ClientManager(QTcpSocket *client, QObject *parent = nullptr);

    void connectToServer();
    void sendMessage(QString const& message);
    void sendName(QString const& name);
    void sendStatus(ChatProtocol::Status status);
    QString name() const;
public slots:
    void sendIsTyping();
signals:
    void connected();
    void disconnected();
    void textMessageReceived(QString message);
    void isTyping();
    void nameChanged(QString name);
    void statusChanged(ChatProtocol::Status status);

private slots:
    void readyRead();

private: // for methods
    void setupClient();
private:
    QTcpSocket *_socket;
    QHostAddress _ip;
    ushort _port;
    ChatProtocol _protocol;
};

#endif // CLIENTMANAGER_H
