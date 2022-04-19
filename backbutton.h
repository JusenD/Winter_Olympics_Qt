#ifndef BACKBUTTON_H
#define BACKBUTTON_H

#include <QPushButton>
#include<QTimer>

class backButton : public QPushButton
{
    Q_OBJECT
public:
  //  explicit MyPushButton(QWidget *parent = nullptr);
   backButton(QString img);

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

#endif // BACKBUTTON_H
