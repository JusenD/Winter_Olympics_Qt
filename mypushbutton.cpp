#include "mypushbutton.h"
#include<QDebug>

//MyPushButton::MyPushButton(QWidget *parent)
//    : QPushButton({parent}
//{

//}
MyPushButton::MyPushButton(QString normalImg, QString pressImg){
    this->normalImg = normalImg;
    this->pressImg = pressImg;
    QPixmap pix;
    pix.load(normalImg);
    //设置图片固定大小
    this->setFixedSize(pix.width()*0.75, pix.height()*0.75);
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width()*0.75, pix.height()*0.75));
    min = 1;
    max = 13;
    now = 1;
    time1 = new QTimer;
    time2 = new QTimer;
    connect(time1, &QTimer::timeout, this, [=](){

        QString str;
        if(pressImg == ":/res/pressSignButton13.png"){
            str = QString(":/res/pressSignButton%1.png").arg(this->now++);
        }
        else if(pressImg == ":/res/pressRegistButton13.png"){
            str = QString(":/res/pressRegistButton%1.png").arg(this->now++);
        }
  //      qDebug()<<str<<"=?"<<pressImg<<"now="<<now;
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width()*0.75, pix.height()*0.75);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.75, pix.height()*0.75));
        if(this->now > max){
            this->now = max;
            time1->stop();
        }
    });
    connect(time2, &QTimer::timeout, this, [=](){

        QString str;
        if(pressImg == ":/res/pressSignButton13.png"){
            str = QString(":/res/pressSignButton%1.png").arg(this->now--);
        }
        else if(pressImg == ":/res/pressRegistButton13.png"){
            str = QString(":/res/pressRegistButton%1.png").arg(this->now--);
        }
 //       qDebug()<<str<<"=?"<<pressImg<<"now="<<now;
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width()*0.75, pix.height()*0.75);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.75, pix.height()*0.75));
        if(this->now < min){
            this->now = min;
            time2->stop();
        }
    });
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(this->pressImg != ""){
        this->time1->stop();
  //      qDebug()<<"鼠标释放";
        this->time2->start(10);
        emit release();
    }
    return QPushButton::mouseReleaseEvent(e);

}

void MyPushButton::enterEvent(QEnterEvent *evnet){
    this->time2->stop();
 //   qDebug()<<"鼠标进入";
    this->time1->start(15);
}
void MyPushButton::leaveEvent(QEvent *event){
    this->time1->stop();
 //   qDebug()<<"鼠标离开";
    this->time2->start(15);
}

