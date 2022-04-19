#ifndef CHANGE_COMMODITY_DIALOG_H
#define CHANGE_COMMODITY_DIALOG_H

#include <QDialog>

namespace Ui {
class change_commodity_dialog;
}

class change_commodity_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit change_commodity_dialog(QWidget *parent, std::string commodityID);
    std::string name, description;
    bool name_ok = true;
    bool description_ok = true;
    void check_name();
    void check_description();
    void paintEvent(QPaintEvent*);
    ~change_commodity_dialog();
signals:
    void save();
private:
    Ui::change_commodity_dialog *ui;
};

#endif // CHANGE_COMMODITY_DIALOG_H
