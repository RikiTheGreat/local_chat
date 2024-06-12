#include "chatprotocol.h"

#include <QDataStream>
#include <QIODevice>

ChatProtocol::ChatProtocol() {}

QByteArray ChatProtocol::textMessage(const QString &message)
{
    return getData(Text, message);
}

QByteArray ChatProtocol::isTypingMessage()
{
    return getData(IsTyping, "");
}

QByteArray ChatProtocol::setNameMessage(const QString &message)
{
    return getData(SetName, message);
}

QByteArray ChatProtocol::setStatus(Status status)
{
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);
    stream << SetStatus << status;
    return ba;
}

void ChatProtocol::loadData(QByteArray data)
{
    QDataStream in(&data, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_6_0);

    in >> _type;
    switch(_type) {
    case Text:
        in >> _message;
        break;
    case SetName:
        in >> _name;
        break;
    case SetStatus:
        in >> _status;
        break;
    }
}


QByteArray ChatProtocol::getData(MessageType type, QString const& data) {
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);
    stream.setVersion(QDataStream::Qt_6_0);
    stream << type << data;

    return ba;
}

ChatProtocol::MessageType ChatProtocol::type() const
{
    return _type;
}

ChatProtocol::Status ChatProtocol::status() const
{
    return _status;
}

QString ChatProtocol::name() const
{
    return _name;
}

QString ChatProtocol::message() const
{
    return _message;
}
