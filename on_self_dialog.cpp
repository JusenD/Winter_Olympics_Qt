#include "on_self_dialog.h"
#include "ui_on_self_dialog.h"
#include"User.h"
#include<smallbutton.h>
#include<QPainter>
#include<QMessageBox>
#include<QDebug>
using namespace std;

extern string GetTime();
extern string GetCommodityID();
on_self_dialog::on_self_dialog(QWidget *parent, string ID) :
    QDialog(parent),
    ui(new Ui::on_self_dialog)
{
    ui->setupUi(this);
    setFixedSize(303, 590);
    setWindowTitle("上架商品");
    //初始化拖拽条
    connect(ui->spinBox, &QSpinBox::valueChanged, ui->horizontalSlider, &QSlider::setValue);
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
    ui->spinBox->setMinimum(1);
    //上架按钮
    SmallButton *on_shelf_btn = new SmallButton(":/res/on_shelfButton");
    on_shelf_btn->move(50, 540);
    on_shelf_btn->setParent(this);
    //返回按钮
    SmallButton *back_btn = new SmallButton(":/res/backButton");
    back_btn->move(180, 540);
    back_btn->setParent(this);
    connect(back_btn, &SmallButton::release, this, [=](){
       this->close();
    });

    //上架操作
    connect(on_shelf_btn, &SmallButton::release, this, [=](){
       if(QMessageBox::Yes == QMessageBox::question(this, "上架", "确认上架此商品？")){
           string name, price, description, number;
           name = ui->name->text().toStdString();
           if(name == ""){
               QMessageBox::information(this, "上架", "商品名称不能为空！");
           }
           else{
           price = ui->price->text().toStdString();
           description = ui->description->toPlainText().toStdString();
           number = to_string(ui->spinBox->value());
           Single_Commodity c;
           c.commodityName = name;
           c.price = price;
           c.number = number;
           c.description = description;
           c.sellerID = ID;
           c.addedDate = GetTime();
           c.state = "销售中";
           c.commodityID = GetCommodityID();
           Commodity j;
           string VALUES = c.commodityID;
           char buffer[500];
           sprintf(buffer, "(%s,%s,%s,%s,%s,%s,%s,%s)", c.commodityID.c_str(), c.commodityName.c_str(),
               c.price.c_str(), c.number.c_str(), c.description.c_str(), c.sellerID.c_str(), c.addedDate.c_str(), c.state.c_str());
           VALUES = buffer;
           j.INSERT(VALUES);
           Commodity::init();
           }
           this->close();

        }
    });
}

void on_self_dialog::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/buyBackground.png");
    painter.drawPixmap(0, 0,303, 590, pix);
}
on_self_dialog::~on_self_dialog()
{
    delete ui;
}
