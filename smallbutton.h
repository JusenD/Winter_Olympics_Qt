#ifndef SmallButton_H
#define SmallButton_H

#include <QPushButton>
#include<QTimer>

class SmallButton : public QPushButton
{
    Q_OBJECT
public:
  //  explicit MyPushButton(QWidget *parent = nullptr);
   SmallButton(QString img);

   QString Img;
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

#endif // SmallButton_H
