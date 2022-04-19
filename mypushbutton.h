#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include<QTimer>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
  //  explicit MyPushButton(QWidget *parent = nullptr);
   MyPushButton(QString normalImg, QString pressImg = "");

   QString normalImg;
   QString pressImg;
   void mouseReleaseEvent(QMouseEvent *e);
   void enterEvent(QEnterEvent *evnet);
   void leaveEvent(QEvent *event);
   int min;
   int max;
   int now;
   QTimer *time1;
   QTimer *time2;
signals:
   void mousePressEvent(QMouseEvent *e);
   void release();
};

#endif // MYPUSHBUTTON_H
