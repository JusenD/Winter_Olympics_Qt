#include "SmallButton.h"
#include<QDebug>

//SmallButton::SmallButton(QWidget *parent)
//    : QPushButton({parent}
//{

//}
SmallButton::SmallButton(QString img){
    this->Img = img;
    QString normalImg = Img.append("1.png");
    QPixmap pix;
    pix.load(normalImg);
    //设置图片固定大小
    this->setFixedSize(pix.width()*0.7, pix.height()*0.7);
    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width()*0.7, pix.height()*0.7));
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
        this->setFixedSize(pix.width()*0.7, pix.height()*0.7);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.7, pix.height()*0.7));
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
        this->setFixedSize(pix.width()*0.7, pix.height()*0.7);
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width()*0.7, pix.height()*0.7));
        if(this->now < min){
            this->now = min;
            time2->stop();
        }
    });
}

void SmallButton::mouseReleaseEvent(QMouseEvent *e){
    this->time1->stop();
//      qDebug()<<"鼠标释放";
    this->time2->start(5);
    emit release();
    return QPushButton::mouseReleaseEvent(e);

}

void SmallButton::enterEvent(QEnterEvent *evnet){
    this->time2->stop();
 //   qDebug()<<"鼠标进入";
    this->time1->start(15);
}
void SmallButton::leaveEvent(QEvent *event){
    this->time1->stop();
 //   qDebug()<<"鼠标离开";
    this->time2->start(15);
}
