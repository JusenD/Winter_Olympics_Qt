#include "register_dialog.h"
#include "ui_register_dialog.h"
#include"mypushbutton.h"
#include<QPainter>
#include<QMessageBox>
#include<QTimer>

#include"User.h"
extern string GetUserID();
register_dialog::register_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::register_dialog)
{
    ui->setupUi(this);
    setFixedSize(320, 616);
    setWindowTitle("注册");
    setWindowIcon(QIcon(":/res/icon.png"));
    //初始红色警示文本
    ui->warning->clear();
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->warning->setPalette(pe);
    //检查用户名
    connect(ui->name, &QLineEdit::editingFinished, this, &register_dialog::check_name);
    //检查密码1、2
    connect(ui->password1, &QLineEdit::editingFinished, this, &register_dialog::check_password1);
    connect(ui->password2, &QLineEdit::editingFinished, this, &register_dialog::check_password2);
    //注册按钮
    MyPushButton * registBtn = new MyPushButton(":/res/registButton.png", ":/res/pressRegistButton13.png");
    registBtn->setParent(this);
    registBtn->move(110, 500);
    connect(registBtn, &MyPushButton::release, this, [=](){
        if(name_ok && password1_ok && password2_ok){
            phone = ui->phoneNumber->text().toStdString();
            adress = ui->adress->text().toStdString();
            Single_User a;
            a.userID = GetUserID(); a.username = name;
            a.password = password1; a.phoneNumber = phone;
            a.adress = adress; a.balance = "0"; a.userState = "正常";
            User::all.push_back(a);
            User::preserve();
            QTimer::singleShot(100, this, [=](){
                QMessageBox::information(this, "注册", "注册成功！");
                this->close();
            });
        }
    });
}

void register_dialog::check_name(){
    name_ok = true;
    qDebug()<<"输入结束";
    name = ui->name->text().toStdString();
    if(name == ""){
        name_ok = false;
        ui->warning->setText("用户名不能为空");
    }
    else if (name.find(' ') != string::npos) {
        name_ok = false;
        ui->warning->setText("用户名中不能有空格");
    }
    else if (name.find(',') != string::npos){
        name_ok = false;
        ui->warning->setText("用户名中不能有逗号");
    }
    else{
        int i = 0;
        for(; i < User::all.size(); i++){
            if(name == User::all[i].username){
                name_ok = false;
                ui->warning->setText("用户名已存在");
                ui->warning->show();
                break;
            }
        }
        if((ui->warning->text() == "用户名中不能有空格" || ui->warning->text() == "用户名中不能有逗号" || ui->warning->text() == "用户名已存在" || ui->warning->text() == "用户名不能为空") && i == User::all.size()){ ui->warning->clear(); check_password1();}
    }

}

void register_dialog::check_password1(){
    password1_ok = true;
    qDebug()<<"输入结束";
    password1 = ui->password1->text().toStdString();
    if(password1 == ""){
        password1_ok = false;
        ui->warning->setText("密码不能为空");
    }
    else if (password1.find(' ') != string::npos) {
        password1_ok = false;
        ui->warning->setText("密码中不能有空格");
    }
    else if (password1.find(',') != string::npos) {
        password1_ok = false;
        ui->warning->setText("密码中不能有逗号");
    }
    else if (ui->warning->text() == "密码中不能有空格" || ui->warning->text() == "密码中不能有逗号" || ui->warning->text() == "密码不能为空") {ui->warning->clear(); check_name();}
    else if(password2 != ""){
        if(password1 != password2){
            password2_ok = false;
            ui->warning->setText("两次输入密码不一致");
        }
        else if(ui->warning->text() == "两次输入密码不一致"){
            password2_ok = true;
            ui->warning->clear();
            check_name();
        }
    }
}

void register_dialog::check_password2(){
    password2_ok = true;
    qDebug()<<"输入结束";
    password2 = ui->password2->text().toStdString();
    if (password1 != password2) {
        password2_ok = false;
        ui->warning->setText("两次输入密码不一致");
    }
    else if(ui->warning->text() == "两次输入密码不一致") {ui->warning->clear(); check_name();}
}

void register_dialog::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/registBackground.png");
    painter.drawPixmap(0, 0, 320, 616, pix);
}
register_dialog::~register_dialog()
{
    delete ui;
}
