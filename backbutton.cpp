#include "backbutton.h"
#include<QDebug>

//backButton::backButton(QWidget *parent)
//    : QPushButton({parent}
//{

//}
backButton::backButton(QString img){
    this->Img = img;
    QString normalImg = Img.append("1.png");
    QPixmap pix;
    pix.load(normalImg);
    //设置图片固定大小
    this->setFixedSize(pix.width(), pix.height());
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(), pix.height()));
    min = 1;
    max = 16;
    now = 1;
    time1 = new QTimer;
    time2 = new QTimer;
    connect(time1, &QTimer::timeout, this, [=](){

        QString str = img;
        str.append(QString("%1.png").arg(this->now++));
  //      qDebug()<<str<<"=?"<<pressImg<<"now="<<now;
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if(this->now > max){
            this->now = max;
            time1->stop();
        }
    });
    connect(time2, &QTimer::timeout, this, [=](){

        QString str = img;
        str.append(QString("%1.png").arg(this->now--));
 //       qDebug()<<str<<"=?"<<pressImg<<"now="<<now;
        QPixmap pix;
        pix.load(str);
        this->setFixedSize(pix.width(), pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(), pix.height()));
        if(this->now < min){
            this->now = min;
            time2->stop();
        }
    });
}

void backButton::mouseReleaseEvent(QMouseEvent *e){
    this->time1->stop();
//      qDebug()<<"鼠标释放";
    this->time2->start(7);
    emit release();
    return QPushButton::mouseReleaseEvent(e);

}

void backButton::enterEvent(QEnterEvent *evnet){
    this->time2->stop();
 //   qDebug()<<"鼠标进入";
    this->time1->start(12);
}
void backButton::leaveEvent(QEvent *event){
    this->time1->stop();
 //   qDebug()<<"鼠标离开";
    this->time2->start(12);
}
