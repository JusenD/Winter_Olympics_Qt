#include "change_commodity_dialog.h"
#include "ui_change_commodity_dialog.h"
#include"Data.h"
#include"smallbutton.h"
#include<QMessageBox>
#include<QPainter>
using namespace std;

extern int Myfind(string);
extern string manipulate(string);
change_commodity_dialog::change_commodity_dialog(QWidget *parent, string commodityID) :
    QDialog(parent),
    ui(new Ui::change_commodity_dialog)
{
    ui->setupUi(this);
    setFixedSize(364, 708);
    setWindowTitle("商品修改");
    int i = Myfind(commodityID);
    //初始化拖拽条
    connect(ui->spinBox, &QSpinBox::valueChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
    ui->spinBox->setMinimum(1);
    //初始化输入框
    ui->name->setText(Commodity::all[i].commodityName.c_str());
    ui->price->setValue(atof(Commodity::all[i].price.c_str()));
    ui->spinBox->setValue(atoi(Commodity::all[i].number.c_str()));
    ui->description->setText(Commodity::all[i].description.c_str());
    if(Commodity::all[i].state == "已下架"){
        ui->state->setChecked(false);
    }else ui->state->setChecked(true);
    //初始化报错
    ui->warning->clear();
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->warning->setPalette(pe);
    //检查用户名
    connect(ui->name, &QLineEdit::editingFinished, this, &change_commodity_dialog::check_name);
    //检查密码1、2
    connect(ui->description, &QTextEdit::textChanged, this, &change_commodity_dialog::check_description);
    //修改按钮
    SmallButton *change_btn = new SmallButton(":/res/changeButton");
    change_btn->setParent(this);
    change_btn->move(200, 640);
    //返回按钮
    SmallButton *back_btn = new SmallButton(":/res/backButton");
    back_btn->setParent(this);
    back_btn->move(80, 640);
    connect(back_btn, &SmallButton::release, this, [=](){
       this->close();
    });
    //修改操作
    connect(change_btn, &SmallButton::release, this, [=](){
        if(name_ok && description_ok){
            QString name, number, price, description;
            name = ui->name->text();
            number = ui->spinBox->text();
            price = ui->price->text();
            description = ui->description->toPlainText();
            if(QMessageBox::Yes == QMessageBox::question(this, "修改", "确认修改？")){
                Commodity::all[i].commodityName = name.toStdString();
                Commodity::all[i].number = number.toStdString();
                Commodity::all[i].price = price.toStdString();
                Commodity::all[i].description = description.toStdString();
                if(ui->state->isChecked() && number != "0") Commodity::all[i].state = "销售中";
                else Commodity::all[i].state = "已下架";
                Commodity::preserve();
                Commodity::Qinit();
                this->close();
                emit save();
            }
        }
    });
}

void change_commodity_dialog::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/buyBackground.png");
    painter.drawPixmap(0, 0, 364, 708, pix);
}

void change_commodity_dialog::check_name(){
    name_ok = true;
    qDebug()<<"输入结束";
    name = ui->name->text().toStdString();
    if(name == ""){
        name_ok = false;
        ui->warning->setText("商品名不能为空");
    }
    else if (name.find(',') != string::npos){
        name_ok = false;
        ui->warning->setText("商品名中不能有逗号");
    }
    else{
        if((ui->warning->text() == "商品名中不能有逗号" || ui->warning->text() == "商品名不能为空")){ ui->warning->clear(); check_description();}
    }
}

void change_commodity_dialog::check_description(){
    description_ok = true;
    qDebug()<<"输入结束";
    description = ui->description->toPlainText().toStdString();
    if (description.find(',') != string::npos){
        description_ok = false;
        ui->warning->setText("描述中不能有逗号");
    }
    else{
        if((ui->warning->text() == "描述中不能有逗号")){ ui->warning->clear(); check_name();}
    }
}

change_commodity_dialog::~change_commodity_dialog()
{
    delete ui;
}
