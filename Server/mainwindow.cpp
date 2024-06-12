#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "clientchatwidget.h"
#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newClientConnected(QTcpSocket *client)
{
    auto id = client->property("id");
    ui->lstClients->addItem(QString("New Client added: %1").arg(id.toInt()));
    auto chatWidget = new ClientChatWidget(client, this);
    ui->clientsTabwidget->addTab(chatWidget, QString("Client (%1)").arg(id.toInt()));

    connect(chatWidget, &ClientChatWidget::nameChanged, this, &MainWindow::setClientName);
    connect(chatWidget, &ClientChatWidget::statusChanged, this, &MainWindow::setClientStatus);
    connect(chatWidget, &ClientChatWidget::isTyping, [this](QString const& text){
        this->statusBar()->showMessage(text, 750);
    });
}

void MainWindow::clientDisconnected(QTcpSocket *client)
{
    auto id = client->property("id");
    ui->lstClients->addItem(QString("Client Disconnected: %1").arg(id.toInt()));
}

void MainWindow::setClientName(const QString &name)
{
    auto widget = qobject_cast<QWidget*>(sender());
    auto index = ui->clientsTabwidget->indexOf(widget);
    ui->clientsTabwidget->setTabText(index, name);
}

void MainWindow::setClientStatus(ChatProtocol::Status status)
{
    auto widget = qobject_cast<QWidget*>(sender());
    auto index = ui->clientsTabwidget->indexOf(widget);

    QString iconPath = ":/icons/";
    QString iconName;

    switch (status) {
    case ChatProtocol::Status::Available:
        iconName = iconPath + "available.png";
        break;
    case ChatProtocol::Status::Away:
        iconName = iconPath + "away.png";
        break;
    case ChatProtocol::Status::Busy:
        iconName = iconPath + "busy.png";
        break;
    }

    ui->clientsTabwidget->setTabIcon(index, QIcon(iconName));
}

void MainWindow::setupServer()
{
    _server = new ServerManager();
    connect(_server, &ServerManager::newClientConnected, this, &MainWindow::newClientConnected);
    connect(_server, &ServerManager::clientDisconnected, this, &MainWindow::clientDisconnected);
}
