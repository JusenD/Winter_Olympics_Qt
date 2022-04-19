#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QMainWindow>

namespace Ui {
class adminWindow;
}

class adminWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit adminWindow(QWidget *parent = nullptr);
    ~adminWindow();
    void paintEvent(QPaintEvent *);
signals:
    void adminCancellation();

private:
    Ui::adminWindow *ui;
    bool can_off = false;
    bool can_ban = false;
};

#endif // ADMINWINDOW_H
