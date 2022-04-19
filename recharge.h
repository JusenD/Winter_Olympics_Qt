#ifndef RECHARGE_H
#define RECHARGE_H

#include <QDialog>

namespace Ui {
class recharge;
}

class recharge : public QDialog
{
    Q_OBJECT

public:
    explicit recharge(QWidget *parent = nullptr);
    ~recharge();

private:
    Ui::recharge *ui;
};

#endif // RECHARGE_H
