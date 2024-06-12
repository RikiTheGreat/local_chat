#include "clientmanager.h"

ClientManager::ClientManager(QHostAddress ip, ushort port, QObject *parent) : QObject{parent}, _ip(ip), _port(port)
{
    _socket = new QTcpSocket(this);
    setupClient();
}

ClientManager::ClientManager(QTcpSocket *client, QObject *parent) : QObject{parent}, _socket(client)
{
    setupClient();
}

void ClientManager::connectToServer()
{
    _socket->connectToHost(_ip, _port);
}

void ClientManager::sendMessage(const QString &message)
{
    _socket->write(_protocol.textMessage(message));
}

void ClientManager::sendName(const QString &name)
{
    _socket->write(_protocol.setNameMessage(name));
}

void ClientManager::sendStatus(ChatProtocol::Status status)
{
    _socket->write(_protocol.setStatus(status));
}

QString ClientManager::name() const
{
    auto id = _socket->property("id").toInt();
    auto name = _protocol.name().length() > 0 ? _protocol.name() : QString("Client (%1)").arg(id);
    return name;
}

void ClientManager::sendIsTyping()
{
    _socket->write(_protocol.isTypingMessage());
}

void ClientManager::readyRead()
{
    auto data = _socket->readAll();
    _protocol.loadData(data);

    switch(_protocol.type()) {
    case ChatProtocol::SetName:
        emit nameChanged(_protocol.name());
        break;
    case ChatProtocol::SetStatus:
        emit statusChanged(_protocol.status());
        break;
    case ChatProtocol::IsTyping:
        emit isTyping();
        break;
    }

    //emit dataReceived(data);
}

void ClientManager::setupClient()
{
    connect(_socket, &QTcpSocket::connected, this, &ClientManager::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientManager::disconnected);
    connect(_socket, &QTcpSocket::readyRead, this, &ClientManager::readyRead);
}
