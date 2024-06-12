#ifndef CLIENTCHATWIDGET_H
#define CLIENTCHATWIDGET_H

#include "clientmanager.h"

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ClientChatWidget;
}

class ClientChatWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientChatWidget(QTcpSocket *client, QWidget *parent = nullptr);
    ~ClientChatWidget();

signals:
    void nameChanged(QString const& name);
    void isTyping(QString const& message);
    void statusChanged(ChatProtocol::Status status);

private slots:
    void on_sendBtn_clicked();
    void clientDisconnected();
    void textMessageReceived(QString const& message);
    void onTyping();
private:
    Ui::ClientChatWidget *ui;
    ClientManager *_client;
};

#endif // CLIENTCHATWIDGET_H
