#ifndef ON_SELF_DIALOG_H
#define ON_SELF_DIALOG_H

#include <QDialog>

namespace Ui {
class on_self_dialog;
}

class on_self_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit on_self_dialog(QWidget *parent, std::string ID);
    void paintEvent(QPaintEvent*);
    ~on_self_dialog();

private:
    Ui::on_self_dialog *ui;
};

#endif // ON_SELF_DIALOG_H
