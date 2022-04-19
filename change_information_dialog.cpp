#include "change_information_dialog.h"
#include "ui_change_information_dialog.h"
#include<QPainter>
#include"User.h"
#include"smallbutton.h"
#include<QMessageBox>
using namespace std;

change_information_dialog::change_information_dialog(QWidget *parent, Single_User *me) :
    QDialog(parent),
    ui(new Ui::change_information_dialog)
{
    ui->setupUi(this);
    this->me = me;
    //初始化输入框
    setWindowTitle("信息修改");
    ui->name->setText(me->username.c_str());
    ui->adress->setText(me->adress.c_str());
    ui->phoneNumber->setText(me->phoneNumber.c_str());
    SmallButton *change_btn = new SmallButton(":/res/changeButton");
    change_btn->setParent(this);
    change_btn->move(50, 440);
    //初始化用户名报错
    ui->warning->clear();
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->warning->setPalette(pe);
    //返回按钮
    SmallButton *back_btn = new SmallButton(":/res/backButton");
    back_btn->setParent(this);
    back_btn->move(150, 440);
    connect(back_btn, &SmallButton::release, this, [=](){
       this->close();
    });
    //用户名检查
    connect(ui->name, &QLineEdit::editingFinished, this, &change_information_dialog::check_name);
    //地址和联系方式检查
    connect(ui->phoneNumber, &QLineEdit::editingFinished, this, &change_information_dialog::check_phone);
    connect(ui->adress, &QTextEdit::textChanged, this, &change_information_dialog::check_description);
    //修改操作
    connect(change_btn, &SmallButton::release, this, [=](){
        if(can_change && phone_ok && description_ok){
        if(QMessageBox::Yes == QMessageBox::question(this, "修改", "确认修改？")){
            string name1, phone, adress;
            name1 = ui->name->text().toStdString();
            phone = ui->phoneNumber->text().toStdString();
            adress = ui->adress->toPlainText().toStdString();
            me->username = name1;
            me->phoneNumber = phone;
            me->adress = adress;
            qDebug()<<phone.c_str()<<adress.c_str();
            User::preserve();
            this->close();
            emit save();
        }
        }
    });

}

void change_information_dialog::check_name(){
    can_change = true;
    qDebug()<<"输入结束";
    name = ui->name->text().toStdString();
    if(name == ""){
        can_change = false;
        ui->warning->setText("用户名不能为空");
    }
    else if (name.find(' ') != string::npos) {
        can_change = false;
        ui->warning->setText("用户名中不能有空格");
    }
    else if (name.find(',') != string::npos){
        can_change = false;
        ui->warning->setText("用户名中不能有逗号");
    }
    else{
        int i = 0;
        for(; i < User::all.size(); i++){
            if(name == User::all[i].username && name != me->username){
                can_change = false;
                ui->warning->setText("用户名已存在");
                ui->warning->show();
                break;
            }
        }
        if((ui->warning->text() == "用户名中不能有空格" || ui->warning->text() == "用户名中不能有逗号" || ui->warning->text() == "用户名已存在" || ui->warning->text() == "用户名不能为空") && i == User::all.size()){ ui->warning->clear(); check_description();check_phone();}
    }

}

void change_information_dialog::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/change_information_background.png");
    painter.drawPixmap(0, 0, 282, 549, pix);
}

void change_information_dialog::check_description(){
    description_ok = true;
    qDebug()<<"输入结束";
    description = ui->adress->toPlainText().toStdString();
    if (description.find(',') != string::npos){
        description_ok = false;
        ui->warning->setText("地址中不能有逗号");
    }
    else{
        if((ui->warning->text() == "地址中不能有逗号")){ ui->warning->clear(); check_name(); check_phone();}
    }
}

void change_information_dialog::check_phone(){
    phone_ok = true;
    qDebug()<<"输入结束";
    phone = ui->phoneNumber->text().toStdString();
    if (phone.find(',') != string::npos){
        phone_ok = false;
        ui->warning->setText("联系方式中不能有逗号");
    }
    else{
        if((ui->warning->text() == "联系方式中不能有逗号")){ ui->warning->clear(); check_name(); check_description();}
    }
}

change_information_dialog::~change_information_dialog()
{
    delete ui;
}
