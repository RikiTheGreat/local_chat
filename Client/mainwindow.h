#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientmanager.h"
#include "chatitemwidget.h"

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
    void on_actionConnect_triggered();
    void dataReceived(QString data);
    void on_sendBtn_clicked();

    void on_nameLineEdit_editingFinished();

    void on_statusComboBox_currentIndexChanged(int index);

    void onTyping();
private:
    Ui::MainWindow *ui;
    ClientManager *_client;
};
#endif // MAINWINDOW_H
