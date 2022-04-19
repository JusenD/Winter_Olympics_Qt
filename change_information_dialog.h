#ifndef CHANGE_INFORMATION_DIALOG_H
#define CHANGE_INFORMATION_DIALOG_H

#include <QDialog>
#include"User.h"

namespace Ui {
class change_information_dialog;
}

class change_information_dialog : public QDialog
{
    Q_OBJECT

public:
    std::string name, phone, description;
    bool can_change = false;
    bool phone_ok = true;
    bool description_ok = true;
    explicit change_information_dialog(QWidget *parent, Single_User *me);
    Single_User* me;
    void paintEvent(QPaintEvent*);
    void check_name();
    void check_phone();
    void check_description();
    ~change_information_dialog();
signals:
    void save();
private:
    Ui::change_information_dialog *ui;
};

#endif // CHANGE_INFORMATION_DIALOG_H
