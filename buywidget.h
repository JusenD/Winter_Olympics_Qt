#ifndef BUYWIDGET_H
#define BUYWIDGET_H

#include <QDialog>
#include"User.h"

namespace Ui {
class buyWidget;
}

class buyWidget : public QDialog
{
    Q_OBJECT

public:
    explicit buyWidget(QWidget *parent, Single_User *user, std::string commodity);
    Single_User *me = NULL;
    std::string CommodityID;
    void paintEvent(QPaintEvent*);
    ~buyWidget();
signals:
    void over();
    void recharge();
private:
    Ui::buyWidget *ui;
};

#endif // BUYWIDGET_H
