#include "adminwindow.h"
#include "ui_adminwindow.h"
#include<QPainter>
#include"Data.h"
#include"backbutton.h"
#include<QMouseEvent>
#include<QTimer>
#include<QMessageBox>
#include"SQL.h"
#include"User.h"

adminWindow::adminWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::adminWindow)
{
    ui->setupUi(this);
    this->setFixedSize(640*1.5, 360*1.5);
    this->setWindowIcon(QIcon(":/res/icon.png"));
    this->setWindowTitle("管理员中心");
    ui->stackedWidget->setCurrentIndex(1);
    //设置单行选中且不可修改
    ui->ban_user_view-> setSelectionBehavior ( QAbstractItemView :: SelectRows );
    ui->ban_user_view->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->ban_user_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->check_commodity_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->check_commodity_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->check_commodity_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->check_order_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->check_order_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->check_order_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->check_user_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->check_user_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->check_user_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->off_shelf_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->off_shelf_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->off_shelf_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->search_commodity_view->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->search_commodity_view->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->search_commodity_view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //注销操作
    connect(ui->cancellation, &QAction::triggered, this, [=](){
        emit adminCancellation();
    });

    //搜索按钮
    backButton *search_btn = new backButton(":/res/searchButton");
    search_btn->hide();
    search_btn->setParent(this);
    search_btn->move(630, 100);
    connect(search_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            string name = ui->commodity_name->text().toStdString();
            int n = 0;
            for(int i = 0; i < Commodity::all.size();i++){
                if(Commodity::all[i].commodityName.find(name) != string::npos) n++;
            }
            ui->search_commodity_view->setColumnCount(7);
            ui->search_commodity_view->setHorizontalHeaderLabels(QStringList()<<"商品ID"<<"名称"<<"价格"<<"数量"<<"卖家ID"<<"上架时间"<<"商品状态");
            ui->search_commodity_view->setRowCount(n);
            int x = 0;
            for(int i = 0;i < Commodity::all.size();i++){
                if(Commodity::Qall[i][1].find(name) == string::npos) continue;
                for(int j = 0; j<8 ; j++){
                    if(j == 4) continue;
                    int num = (j < 4) ? j : j-1;
                    QString str = Commodity::Qall[i][j].c_str();
                    QTableWidgetItem *item = new QTableWidgetItem(str);
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->search_commodity_view->setItem(x, num, item);
                }
                x++;
            }
            if(n == 0) QMessageBox::information(this, "查找", "未找到相关商品");
        });
    });
    //下架按钮+搜索按钮
    backButton *search_btn2 = new backButton(":/res/searchButton");
    search_btn2->hide();
    search_btn2->setParent(this);
    search_btn2->move(510, 100);
    connect(search_btn2, &backButton::release, this, [=](){
        this->can_off = false;
        QTimer::singleShot(150, this, [=](){
            string ID = ui->commodity_ID->text().toStdString();
            int n = 0;
            for(int i = 0; i < Commodity::all.size();i++){
                if(Commodity::all[i].commodityID.find(ID) != string::npos) n++;
            }
            ui->off_shelf_view->setColumnCount(7);
            ui->off_shelf_view->setHorizontalHeaderLabels(QStringList()<<"商品ID"<<"名称"<<"价格"<<"数量"<<"卖家ID"<<"上架时间"<<"商品状态");
            ui->off_shelf_view->setRowCount(n);
            int x = 0;
            for(int i = 0;i < Commodity::all.size();i++){
                if(Commodity::Qall[i][0].find(ID) == string::npos) continue;
                for(int j = 0; j<8 ; j++){
                    if(j == 4) continue;
                    int num = (j < 4) ? j : j-1;
                    QString str = Commodity::Qall[i][j].c_str();
                    QTableWidgetItem *item = new QTableWidgetItem(str);
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->off_shelf_view->setItem(x, num, item);
                }
                x++;
            }
            if(n == 0){
                QMessageBox::information(this, "查找", "未找到该商品", "确认");
            }
//            else if(n != 1) QMessageBox::information(this, "查找", "请查找下架单个商品", "确认");
            else if(n == 1){
                this->can_off = true;
            }
        });
    });
    //下架按钮
    backButton *off_btn = new backButton(":/res/offButton");
    off_btn->hide();
    off_btn->setParent(this);
    off_btn->move(680, 100);
    connect(off_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            QList items = ui->off_shelf_view->selectedItems();
            if(!this->can_off && items.empty()) QMessageBox::information(this, "下架", "暂未指定商品", "确认");
            else{
                string ID = ui->commodity_ID->text().toStdString();
                if(!items.empty()) ID = items.at(0)->text().toStdString();
                qDebug()<<ID.c_str();
                bool whether =(QMessageBox::Yes == QMessageBox::question(this, "下架", "确认下架此商品？"));
                if(whether){
                    string instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 商品ID = ";
                    instruction.append(ID);
                    SQL a;
                    a.operate(instruction, 1, "0");
                    Commodity::Qinit();
                    QMessageBox::information(this, "下架", "下架成功！", "确认");
                    QTableWidgetItem *item = new QTableWidgetItem("已下架");
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->off_shelf_view->setItem(ui->off_shelf_view->row(items.at(0)), 6, item);
                }
            }

        });
    });
    //封禁+搜索按钮
    backButton *search_btn3 = new backButton(":/res/searchButton");
    search_btn3->hide();
    search_btn3->setParent(this);
    search_btn3->move(510, 100);
    connect(search_btn3, &backButton::release, this, [=](){
        this->can_ban = false;
        QTimer::singleShot(150, this, [=](){
            string ID = ui->user_ID->text().toStdString();
            int n = 0;
            for(int i = 0; i < User::all.size();i++){
                if(User::all[i].userID.find(ID) != string::npos) n++;
            }
            ui->ban_user_view->setColumnCount(7);
            ui->ban_user_view->setHorizontalHeaderLabels(QStringList()<<"用户ID"<<"用户名"<<"密码"<<"联系方式"<<"地址"<<"钱包余额"<<"用户状态");
            ui->ban_user_view->setRowCount(n);
            int x = 0;
            for(int i = 0;i < User::all.size();i++){
                if(User::Qall[i][0].find(ID) == string::npos) continue;
                for(int j = 0; j<7 ; j++){
                    int num = j;
                    QString str = User::Qall[i][j].c_str();
                    QTableWidgetItem *item = new QTableWidgetItem(str);
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->ban_user_view->setItem(x, num, item);
                }
                x++;
            }
            if(n == 0){
                QMessageBox::information(this, "查找", "未找到该用户", "确认");
            }
//            else if(n != 1) QMessageBox::information(this, "查找", "请查找封禁单个用户", "确认");
            else if(n == 1){
                this->can_ban = true;
            }
        });
    });
    //封禁按钮
    backButton *ban_btn = new backButton(":/res/banButton");
    ban_btn->hide();
    ban_btn->setParent(this);
    ban_btn->move(680, 100);
    connect(ban_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            QList itemss = ui->ban_user_view->selectedItems();
            if(!this->can_ban && itemss.empty()) QMessageBox::information(this, "封禁", "暂未指定用户", "确认");
            else{
                string ID = ui->user_ID->text().toStdString();
                if(!itemss.empty()) ID = itemss.at(0)->text().toStdString();
                bool whether =(QMessageBox::Yes == QMessageBox::question(this, "封禁", "确认封禁此用户？"));
                if(whether){
                    SQL a;
                    string instruction = "UPDATE user SET 用户状态 = 封禁 WHERE 用户ID = ";
                    instruction.append(ID);
                    a.operate(instruction, 1, "0");
                    instruction = "UPDATE commodity SET 商品状态 = 已下架 WHERE 卖家ID = ";
                    instruction.append(ID);
                    a.operate(instruction, 1, "0");
                    User::Qinit();
                    QMessageBox::information(this, "封禁", "封禁成功！", "确认");
                    QTableWidgetItem *item = new QTableWidgetItem("封禁");
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->ban_user_view->setItem(ui->ban_user_view->row(itemss.at(0)), 6, item);
                }
            }

        });
    });
    //返回按钮
    backButton *btn = new backButton(":/res/backButton");
    btn->hide();
    btn->setParent(this);
    btn->move(this->width()*0.8, this->height()*0.9);
    connect(btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            ui->stackedWidget->setCurrentIndex(1);
            search_btn->hide();
            search_btn2->hide();
            search_btn3->hide();
            off_btn->hide();
            btn->hide();
            ban_btn->hide();
        });
    });
    //查看所有商品  商品ID,名称,价格,数量,描述,卖家ID,上架时间,商品状态
    connect(ui->actioncheck_commodity, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(0);
       search_btn->hide();
       search_btn2->hide();
       search_btn3->hide();
       off_btn->hide();
       ban_btn->hide();
       btn->show();
       ui->check_commodity_view->setColumnCount(7);
       ui->check_commodity_view->setHorizontalHeaderLabels(QStringList()<<"商品ID"<<"名称"<<"价格"<<"数量"<<"卖家ID"<<"上架时间"<<"商品状态");
       ui->check_commodity_view->setRowCount(Commodity::all.size());
          //设置正文
       for(int i = 0;i < 8*Commodity::all.size();i++){
           if(i%8 == 7) continue;
           int num = (i % 8 < 4)? i%8 : i%8 + 1;
           QString str = Commodity::Qall[i/8][num].c_str();
           QTableWidgetItem *item =  new QTableWidgetItem(str);
           item->setTextAlignment(Qt::AlignCenter);
           ui->check_commodity_view->setItem(i/8, i%8, item);
       }
    });

    //搜索商品
    connect(ui->actionsearch, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(2);
       search_btn->show();
       search_btn2->hide();
       search_btn3->hide();
       off_btn->hide();
       ban_btn->hide();
       btn->show();
    });
    //下架商品
    connect(ui->actionoff_shelf, &QAction::triggered, this, [=](){
        ui->stackedWidget->setCurrentIndex(3);
        search_btn->hide();
        search_btn2->show();
        search_btn3->hide();
        off_btn->show();
        ban_btn->hide();
        btn->show();
    });
    //查看订单 订单ID,商品ID,交易单价,数量,交易时间,卖家ID,买家ID
    connect(ui->actioncheck_order, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(4);
       search_btn->hide();
       search_btn2->hide();
       search_btn3->hide();
       off_btn->hide();
       ban_btn->hide();
       btn->show();
       ui->check_order_view->setColumnCount(7);
       ui->check_order_view->setHorizontalHeaderLabels(QStringList()<<"订单ID"<<"商品ID"<<"交易单价"<<"数量"<<"交易时间"<<"卖家ID"<<"买家ID");
       ui->check_order_view->setRowCount(Order::all.size());
          //设置正文
       for(int i = 0;i < 7*Order::all.size();i++){
           int num = i%7;
           QString str = Order::Qall[i/7][num].c_str();
           QTableWidgetItem *item =  new QTableWidgetItem(str);
           item->setTextAlignment(Qt::AlignCenter);
           ui->check_order_view->setItem(i/7, i%7, item);
       }
    });
    //查看用户 用户ID,用户名,密码,联系方式,地址,钱包余额,用户状态
    connect(ui->actioncheck_user, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(5);
       search_btn->hide();
       search_btn2->hide();
       search_btn3->hide();
       off_btn->hide();
       ban_btn->hide();
       btn->show();
       ui->check_user_view->setColumnCount(7);
       ui->check_user_view->setHorizontalHeaderLabels(QStringList()<<"用户ID"<<"用户名"<<"密码"<<"联系方式"<<"地址"<<"钱包余额"<<"用户状态");
       ui->check_user_view->setRowCount(Order::all.size());
          //设置正文
       for(int i = 0;i < 7*User::all.size();i++){
           int num = i%7;
           QString str = User::Qall[i/7][num].c_str();
           QTableWidgetItem *item =  new QTableWidgetItem(str);
           item->setTextAlignment(Qt::AlignCenter);
           ui->check_user_view->setItem(i/7, i%7, item);
       }
    });
    //封禁用户
    connect(ui->actionban_user, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(6);
       search_btn->hide();
       search_btn2->hide();
       off_btn->hide();
       btn->show();
       search_btn3->show();
       ban_btn->show();
    });
}

adminWindow::~adminWindow()
{
    delete ui;
}

void adminWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/redBackground.png");
    painter.drawPixmap(0, 0,640*1.5, 360*1.5, pix);
}
