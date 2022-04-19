#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include"User.h"

namespace Ui {
class userWindow;
}

class userWindow : public QMainWindow
{
    Q_OBJECT

public:
    static Single_User *me;
    explicit userWindow(QWidget *parent = nullptr);
    ~userWindow();
    void paintEvent(QPaintEvent *);
signals:
    void userCancellation();
private:
    Ui::userWindow *ui;
    bool can_buy = false;
    bool can_change = false;
};

#endif // USERWINDOW_H
