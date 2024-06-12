#include "chatitemwidget.h"
#include "ui_chatitemwidget.h"
#include <QDateTime>

ChatItemWidget::ChatItemWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ChatItemWidget)
{
    ui->setupUi(this);
}

ChatItemWidget::~ChatItemWidget()
{
    delete ui;
}

void ChatItemWidget::setMessage(const QString &message, bool isMyMessage)
{
    if(isMyMessage) {
        ui->lblMessage->setAlignment(Qt::AlignRight);
        ui->lblTime->setAlignment(Qt::AlignLeft);
    }else {
        ui->lblMessage->setAlignment(Qt::AlignLeft);
        ui->lblTime->setAlignment(Qt::AlignRight);

    }
    ui->lblMessage->setText(message);
    ui->lblTime->setText(QDateTime::currentDateTime().time().toString());
}
