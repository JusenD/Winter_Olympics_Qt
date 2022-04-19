#ifndef REGISTER_DIALOG_H
#define REGISTER_DIALOG_H

#include <QDialog>

namespace Ui {
class register_dialog;
}

class register_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit register_dialog(QWidget *parent = nullptr);
    std::string name, password1, password2, phone, adress;
    bool name_ok = true;
    bool password1_ok = false;
    bool password2_ok = false;
    void paintEvent(QPaintEvent*);
    void check_name();
    void check_password1();
    void check_password2();
    ~register_dialog();

private:
    Ui::register_dialog *ui;
};

#endif // REGISTER_DIALOG_H
