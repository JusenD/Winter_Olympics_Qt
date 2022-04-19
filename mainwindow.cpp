#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include"User.h"
#include<QMessageBox>
#include<QMouseEvent>
#include<QDebug>
#include"register_dialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //设置固定大小
    setFixedSize(312, 562);
    //设置图标
    setWindowIcon(QIcon(":/res/icon.png"));
    //设置标题
    setWindowTitle("冬奥纪念品交易平台");
    //用户窗口
    userwindow = new userWindow;
    //返回主页面
    connect(userwindow, &userWindow::userCancellation, this, [=](){
       userwindow->hide();
       this->show();
    });
    //管理员窗口
    adminwindow = new adminWindow;
    connect(adminwindow, &adminWindow::adminCancellation, this, [=](){
        adminwindow->hide();
        this->show();
    });
    //登录按钮
    MyPushButton * signBtn = new MyPushButton(":/res/pressSignButton1", ":/res/pressSignButton13.png");
    signBtn->setParent(this);
    signBtn->move(this->width() * 0.33 - signBtn->width() * 0.5, 470);
    connect(signBtn, &MyPushButton::release, this, [=](){
        string name = ui->lineEdit->text().toStdString();
        string password = ui->lineEdit_2->text().toStdString();
        qDebug() << "name = "<<ui->lineEdit->text()<<"password = "<<ui->lineEdit_2->text();
        if(ui->checkBox->checkState()==Qt::Unchecked){
        User u; unsigned long long int i = 0; bool whether = false, ban = false;
            while (i < u.all.size()  ) {
                if (name == u.all[i].username && password == u.all[i].password) {
                    if (u.all[i].userState == "正常") whether = true;
                    else ban = true;
                    break;
                }
                i++;
            }
            if (whether) {
                QMessageBox::information(this, "登录", "登陆成功", "确认");
                QTimer::singleShot(250, this, [=](){
                    userWindow::me = &u.all[i];
                    //自身隐藏
                    this->hide();
                    //显示用户场景
                    userwindow->show();
                });
            }
            else if(!ban){
                QMessageBox::warning(this, "登录", "账号或密码错误", "确认");
            }
            else {
                QMessageBox::warning(this, "登录", "用户已被封禁", "确认");
            }
        }else{
            if(name == "admin" && password == "1234567"){
                QMessageBox::information(this, "登录", "管理员登陆成功", "确认");
                QTimer::singleShot(250, this, [=](){
                    this->hide();
                    adminwindow->show();
                });
            }else{
                QMessageBox::warning(this, "登录", "账号或密码错误", "确认");
            }
        }
    });
    //注册按钮
    MyPushButton * registBtn = new MyPushButton(":/res/registButton.png", ":/res/pressRegistButton13.png");
    registBtn->setParent(this);
    registBtn->move(this->width() * 0.67 - signBtn->width() * 0.5, 470);
    connect(registBtn, &MyPushButton::release, this, [=](){
        register_dialog *regist = new register_dialog;
        regist->show();
    });

//    //创建用户界面，延时进入
//    userwindow = new userWindow;
//    connect(userwindow, &userWindow::userCancellation, this, [=](){
//       userwindow->hide();
//       this->show();
//    });//返回主页面
//    connect(signBtn, &MyPushButton::clicked, [=](){
//        QTimer::singleShot(250, this, [=](){
//            //自身隐藏
//            this->hide();
//            //显示用户场景
//            userwindow->show();
//        });
//    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *){
    //设置背景图片
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/signBackground.png");
    painter.drawPixmap(0, 0,this->width(), 592, pix);
}

