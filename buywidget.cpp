#include "buywidget.h"
#include "ui_buywidget.h"
#include"Data.h"
#include"User.h"
#include"SQL.h"
#include<QMessageBox>
#include"smallbutton.h"
#include"order_complete.h"
#include<QPainter>
using namespace std;

extern int Myfind(string);
extern int find_seller(string);
extern string GetTime();
extern string GetOrderID();
string manipulate(string a){
    string result;
    int i = a.find('.');
    result = a.substr(0, i + 2);
    return result;
}
buyWidget::buyWidget(QWidget *parent, Single_User* user, string commodity) :
    QDialog(parent),
    ui(new Ui::buyWidget)
{
    ui->setupUi(this);
    setWindowTitle("购买");
    //将spinbox和slider链接
    connect(ui->spinBox, &QSpinBox::valueChanged, ui->horizontalSlider, &QSlider::setValue);
    //将slider和spinbox链接
    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
    setFixedSize(303, 590);
    me = user;
    CommodityID = commodity;
    int i = Myfind(CommodityID);
    ui->spinBox->setMaximum(atoi(Commodity::all[i].number.c_str()));
    ui->spinBox->setMinimum(1);
//    qDebug()<<"下标i ="<<i<<"数量为"<<Commodity::all[i].number.c_str();
    ui->horizontalSlider->setMaximum(atoi(Commodity::all[i].number.c_str()));
    ui->horizontalSlider->setMinimum(1);
    //购买按钮
    SmallButton *buy_btn = new SmallButton(":/res/buyButton");
    buy_btn->move(50, 540);
    buy_btn->setParent(this);
    //返回按钮
    SmallButton *back_btn = new SmallButton(":/res/backButton");
    back_btn->move(180, 540);
    back_btn->setParent(this);
    connect(back_btn, &SmallButton::release, this, [=](){
       emit over();
    });
    //显示商品信息
    QString name = "";
    QString description = "";
    QString price = "";
    name.append(Commodity::all[i].commodityName.c_str());
    description.append(Commodity::all[i].description.c_str());
    price.append(Commodity::all[i].price.c_str());
    qDebug()<<"name ="<<name<<"desription ="<<description<<"price ="<<price;
    ui->description->setWordWrap(true);
    ui->name->setText(name);
    ui->description->setText(description);
    ui->price->setText(price);

    //购买操作
    connect(buy_btn, &SmallButton::release, this, [=](){
        int num = ui->spinBox->value();
        double Buybalance = atof(me->balance.c_str()) - atof(Commodity::all[i].price.c_str()) * num;
        if (Buybalance < 0) {
            if(QMessageBox::Yes == QMessageBox::question(this, "购买", "余额不足！是否充值")){
                emit recharge();
            }
            emit over();
        }
        else{
            string sellID = Commodity::all[i].sellerID;
            int j = find_seller(sellID);
            double Sellbalance = atoi(User::all[j].balance.c_str()) + atoi(Commodity::all[i].price.c_str()) * num;
            me->balance = manipulate(to_string(Buybalance));
            User::all[j].balance = manipulate(to_string(Sellbalance));
            User::preserve();
            SQL a;
            string instruction = "INSERT INTO order VALUES ";
            string VALUES; char v[100];
            string time = GetTime();
            sprintf(v, "(%s,%s,%s,%s,%s,%s,%s)", GetOrderID().c_str(), Commodity::all[i].commodityID.c_str(),
                Commodity::all[i].price.c_str(), to_string(num).c_str(), time.c_str(), sellID.c_str(), me->userID.c_str());
            VALUES = v;
            instruction.append(v);
            a.operate(instruction, 2, me->userID);
            int n = atoi(Commodity::all[i].number.c_str()) - num;
            string number = to_string(n);
            instruction = "UPDATE commodity SET 数量 = ";
            instruction.append(number).append(" WHERE 商品ID = ").append(CommodityID);
            a.operate(instruction, 2, me->userID);
            order_complete *order = new order_complete(this, time, Commodity::all[i].price, to_string(num), me->balance);
            Order::Qinit();
            order->show();
            emit over();
        }
    });


}

void buyWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;

    pix.load(":/res/buyBackground.png");
    painter.drawPixmap(0, 0,303, 590, pix);
}

buyWidget::~buyWidget()
{
    delete ui;
}
