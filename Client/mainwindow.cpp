#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionConnect_triggered()
{
    _client = new ClientManager();
    connect(_client, &ClientManager::connected, [this]{
        ui->centralwidget->setEnabled(true);
    });

    connect(_client, &ClientManager::disconnected, [this]{
        ui->centralwidget->setEnabled(false);
    });

    connect(_client, &ClientManager::textMessageReceived, this, &MainWindow::dataReceived);
    connect(_client, &ClientManager::nameChanged, this, &MainWindow::setWindowTitle);
    connect(_client, &ClientManager::isTyping, this, &MainWindow::onTyping);

    connect(ui->messageLineEdit, &QLineEdit::textChanged, _client, &ClientManager::sendIsTyping);
    _client->connectToServer();
}

void MainWindow::dataReceived(QString data)
{
    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(data);
    auto listItemWidget = new QListWidgetItem();
    listItemWidget->setSizeHint(QSize(0,65));
    ui->messagesListWidget->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(167,123, 237));
    ui->messagesListWidget->setItemWidget(listItemWidget, chatWidget);
}


void MainWindow::on_sendBtn_clicked()
{
    auto message = ui->messageLineEdit->text().trimmed();
    _client->sendMessage(message);

    auto chatWidget = new ChatItemWidget(this);
    chatWidget->setMessage(message, true);
    auto listItemWidget = new QListWidgetItem();

    listItemWidget->setSizeHint(QSize(0,65));
    ui->messagesListWidget->addItem(listItemWidget);
    listItemWidget->setBackground(QColor(222,123, 237));
    ui->messagesListWidget->setItemWidget(listItemWidget, chatWidget);


    ui->messageLineEdit->clear();
}


void MainWindow::on_nameLineEdit_editingFinished()
{
    auto name = ui->nameLineEdit->text().trimmed();
    _client->sendName(name.toUtf8());
}


void MainWindow::on_statusComboBox_currentIndexChanged(int index)
{
    auto status = (ChatProtocol::Status)index;
    _client->sendStatus(status);
}

void MainWindow::onTyping()
{
    statusBar()->showMessage("Server is typing ...", 750);
}

