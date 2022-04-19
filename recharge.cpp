#include "recharge.h"
#include "ui_recharge.h"

recharge::recharge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recharge)
{
    ui->setupUi(this);
}

recharge::~recharge()
{
    delete ui;
}
