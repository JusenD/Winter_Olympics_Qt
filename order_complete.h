#ifndef ORDER_COMPLETE_H
#define ORDER_COMPLETE_H

#include <QDialog>
using namespace std;

namespace Ui {
class order_complete;
}

class order_complete : public QDialog
{
    Q_OBJECT

public:
    explicit order_complete(QWidget *parent, string time, string price, string number, string balance);
    void paintEvent(QPaintEvent*);
    ~order_complete();

private:
    Ui::order_complete *ui;
};

#endif // ORDER_COMPLETE_H
