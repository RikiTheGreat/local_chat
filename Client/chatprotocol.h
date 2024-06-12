#ifndef CHATPROTOCOL_H
#define CHATPROTOCOL_H
#include <QByteArray>
#include <QString>

class ChatProtocol
{
public:
    enum MessageType {
        Text,
        File,
        IsTyping,
        SetName,
        SetStatus
    };

    enum Status {
        None,
        Available,
        Away,
        Busy
    };

    ChatProtocol();

    QByteArray textMessage(QString const& message);
    QByteArray isTypingMessage();
    QByteArray setNameMessage(QString const& message);
    QByteArray setStatus(Status status);

    void loadData(QByteArray data);

    QString message() const;

    QString name() const;

    ChatProtocol::Status status() const;

    MessageType type() const;

private:
    QByteArray getData(MessageType type, QString const& data);

private:
    MessageType _type;
    QString _message;
    QString _name;
    Status _status;
};

#endif // CHATPROTOCOL_H
