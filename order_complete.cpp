#include "order_complete.h"
#include "ui_order_complete.h"
#include<QPainter>

order_complete::order_complete(QWidget *parent, string time, string price, string number, string balance) :
    QDialog(parent),
    ui(new Ui::order_complete)
{
    ui->setupUi(this);
    setFixedSize(303, 590);
    setWindowTitle("订单完成");
    QString t = "交易时间：";
    QString p = "交易单价：";
    QString n = "交易数量：";
    QString b = "您的余额：";
    t.append(time.c_str());
    p.append(price.c_str());
    n.append(number.c_str());
    b.append(balance.c_str());
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    ui->time->setPalette(pe);
    ui->price->setPalette(pe);
    ui->number->setPalette(pe);
    ui->balance->setPalette(pe);
    ui->time->setText(t);
    ui->price->setText(p);
    ui->number->setText(n);
    ui->balance->setText(b);
    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        this->close();
    });
}

void order_complete::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/newBackground");
    painter.drawPixmap(0, 0, 303, 590, pix);
}

order_complete::~order_complete()
{
    delete ui;
}
