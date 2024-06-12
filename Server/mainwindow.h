#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "chatprotocol.h"
#include "servermanager.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void newClientConnected(QTcpSocket *client);
    void clientDisconnected(QTcpSocket* client);
    void setClientName(QString const& name);
    void setClientStatus(ChatProtocol::Status status);
private: //methods
    void setupServer();
private:
    Ui::MainWindow *ui;
    ServerManager *_server;
};
#endif // MAINWINDOW_H
