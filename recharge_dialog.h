#ifndef RECHARGE_DIALOG_H
#define RECHARGE_DIALOG_H

#include <QDialog>
#include"User.h"

namespace Ui {
class recharge_dialog;
}

class recharge_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit recharge_dialog(QWidget *parent, Single_User *me);
    void paintEvent(QPaintEvent*);
    ~recharge_dialog();
signals:
    void save();
private:
    Ui::recharge_dialog *ui;
};

#endif // RECHARGE_DIALOG_H
