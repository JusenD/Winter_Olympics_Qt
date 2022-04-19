#include "recharge_dialog.h"
#include "ui_recharge_dialog.h"
#include"smallbutton.h"
#include<QtDebug>
#include<QPainter>
#include<QMessageBox>
using namespace std;

extern string manipulate(string);
recharge_dialog::recharge_dialog(QWidget *parent, Single_User *me) :
    QDialog(parent),
    ui(new Ui::recharge_dialog)
{
    ui->setupUi(this);
    setFixedSize(350, 594);
    setWindowTitle("充值");
    SmallButton *recharge_btn = new SmallButton(":/res/rechargeButton");
    recharge_btn->move(70, 490);
    recharge_btn->setParent(this);
    SmallButton *back_btn = new SmallButton(":/res/backButton");
    back_btn->move(190, 490);
    back_btn->setParent(this);
    connect(back_btn, &SmallButton::release, this, [=](){
       this->close();
    });
    //充值功能
    connect(recharge_btn, &SmallButton::release, this, [=](){
        double number;
        number = ui->doubleSpinBox->value();
        number = number + atof(me->balance.c_str());
        string balance = manipulate(to_string(number));
        me->balance = balance;
        User::preserve();
        User::Qinit();
        emit save();
        QMessageBox::information(this, "充值", "充值成功！");
        this->close();
    });

}

void recharge_dialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/rechargeBackground.png");
    painter.drawPixmap(0, 0, 350, 594, pix);
}

recharge_dialog::~recharge_dialog()
{
    delete ui;
}
