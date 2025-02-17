#include "clientchatwidget.h"
#include "ui_clientchatwidget.h"

ClientChatWidget::ClientChatWidget(QTcpSocket* client, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientChatWidget)
{
    ui->setupUi(this);
    _client = new ClientManager(client, this);


    connect(_client, &ClientManager::disconnected, this, &ClientChatWidget::clientDisconnected);
    connect(_client, &ClientManager::textMessageReceived, this, &ClientChatWidget::textMessageReceived);
    connect(_client, &ClientManager::isTyping, this, &ClientChatWidget::onTyping);
    connect(_client, &ClientManager::nameChanged, this, &ClientChatWidget::nameChanged);
    connect(_client, &ClientManager::statusChanged, this, &ClientChatWidget::statusChanged);
    connect(ui->messageLineEdit, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);
}



ClientChatWidget::~ClientChatWidget()
{
    delete ui;
}


void ClientChatWidget::on_sendBtn_clicked()
{
    auto message = ui->messageLineEdit->text().trimmed();
    _client->sendMessage(message);
    ui->messageLineEdit->clear();
    ui->messages->addItem(message);
}

void ClientChatWidget::clientDisconnected()
{
    ui->sendBtn->setEnabled(false);
}

void ClientChatWidget::textMessageReceived(const QString &message)
{
    ui->messages->addItem(message);
}

void ClientChatWidget::onTyping()
{
    emit isTyping(QString("%1 is typing...").arg(_client->name()));
}

