#include "userwindow.h"
#include "ui_userwindow.h"
#include<QPainter>
#include"backbutton.h"
#include"Data.h"
#include<QMessageBox>
#include<QDialog>
#include"buywidget.h"
#include"change_commodity_dialog.h"
#include"change_information_dialog.h"
#include"recharge_dialog.h"
#include<on_self_dialog.h>

Single_User* userWindow::me = NULL;
userWindow::userWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::userWindow)
{
    ui->setupUi(this);
    this->setFixedSize(640*1.5, 360*1.5);
    this->setWindowIcon(QIcon(":/res/icon.png"));
    this->setWindowTitle("用户中心");
    ui->stackedWidget->setCurrentIndex(0);
    //设置只能单行选中且不可修改
    ui->buyer_table-> setSelectionBehavior ( QAbstractItemView :: SelectRows );
    ui->buyer_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->buyer_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->seller_table-> setSelectionBehavior ( QAbstractItemView :: SelectRows );
    ui->seller_table->setSelectionMode ( QAbstractItemView::SingleSelection);
    ui->seller_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->buyer_order_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->buyer_order_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->buyer_order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->seller_order_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->seller_order_table->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->seller_order_table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //搜索按钮
    backButton *sou_btn = new backButton(":/res/souButton");
    sou_btn->hide();
    sou_btn->setParent(this);
    sou_btn->move(445, 100);
    connect(sou_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            string name = ui->commodity_name->text().toStdString();
            int n = 0;
            for(int i = 0; i < Commodity::all.size();i++){
                if(Commodity::all[i].state == "已下架") continue;
                if(Commodity::all[i].commodityName.find(name) != string::npos) n++;
            }
            ui->buyer_table->clearContents();
            ui->buyer_table->setRowCount(n);
            int x = 0, y = 0;
            for(int i = 0;i < Commodity::all.size();i++){
                if(Commodity::Qall[i][1].find(name) == string::npos || Commodity::all[i].state == "已下架") continue;
                for(int j = 0; j<8 ; j++){
                    if(j == 4 || j == 3 || j == 7) continue;
                    QString str = Commodity::Qall[i][j].c_str();
                    QTableWidgetItem *item = new QTableWidgetItem(str);
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->buyer_table->setItem(x, y % 5, item);
                    y++;
                }
                x++;
            }
            if(n == 0){
                QMessageBox::information(this, "查找", "未找到该商品", "确认");
            }
        });
    });
    //全部商品按钮
    backButton *all_btn = new backButton(":/res/allButton");
    all_btn->hide();
    all_btn->setParent(this);
    all_btn->move(615, 100);
    connect(all_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            emit ui->actionbuyer->triggered();
        });
    });
    //商家搜索
    backButton *search_btn = new backButton(":/res/searchButton");
    search_btn->hide();
    search_btn->setParent(this);
    search_btn->move(460, 100);
    connect(search_btn, &backButton::release, this, [=](){
        this->can_change = false;
        QTimer::singleShot(150, this, [=](){
            string ID = ui->commodity_ID->text().toStdString();
            int n = 0;
            for(int i = 0; i < Commodity::all.size();i++){
                if(Commodity::all[i].commodityID.find(ID) != string::npos && Commodity::all[i].sellerID == me->userID) n++;
            }
            ui->seller_table->clearContents();
            ui->seller_table->setRowCount(n);
            int x = 0, num = 0;
            for(int i = 0;i < Commodity::all.size();i++){
                if(Commodity::Qall[i][0].find(ID) == string::npos || Commodity::all[i].sellerID != me->userID) continue;
                for(int j = 0; j<8 ; j++){
                    if(j == 5 || j == 4) continue;
                    QString str = Commodity::Qall[i][j].c_str();
                    QTableWidgetItem *item = new QTableWidgetItem(str);
                    item->setTextAlignment(Qt::AlignCenter);
                    ui->seller_table->setItem(x, num % 6, item);
                    num++;
                }
                x++;
            }
            if(n == 0){
                QMessageBox::information(this, "查找", "未找到该商品", "确认");
            }
            else if(n == 1){
                this->can_change = true;
            }
        });
    });
    //修改按钮
    backButton *change_btn = new backButton(":/res/changeButton");
    change_btn->hide();
    change_btn->setParent(this);
    change_btn->move(615, 100);
    connect(change_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            QList item = ui->seller_table->selectedItems();
            if(!this->can_change && item.empty()) QMessageBox::information(this, "修改", "暂未指定商品", "确认");
            else{
                string ID;
                if(item.empty()) ID = ui->commodity_ID->text().toStdString();
                else ID = item.at(0)->text().toStdString();
                change_commodity_dialog* change_dlg = new change_commodity_dialog(this, ID);
                change_dlg->show();
                connect(change_dlg, &change_commodity_dialog::save, this, [=](){
                   emit search_btn->release();
                });
            }
        });
    });
    //购买按钮
    backButton *buy_btn = new backButton(":/res/buyButton");
    buy_btn->hide();
    buy_btn->setParent(this);
    buy_btn->move(this->width()*0.63+10, this->height()*0.85);

    //充值按钮
    backButton *recharge_btn = new backButton(":/res/rechargeButton");
    recharge_btn->hide();
    recharge_btn->setParent(this);
    recharge_btn->move(490, 130);
    connect(recharge_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            recharge_dialog *recharge_dlg = new recharge_dialog(this, me);
            recharge_dlg->show();
            connect(recharge_dlg, &recharge_dialog::save, this, [=](){
               emit ui->actioninformation->triggered();
            });
        });
    });

    //购买功能
    connect(buy_btn, &backButton::release, this, [=](){
        QList item = ui->buyer_table->selectedItems();
        if(item.empty()){
            QMessageBox::information(this, "购买", "请先选中商品");
        }
        else{
            QTimer::singleShot(150, this, [=](){
                int row = ui->buyer_table->row(item.at(0));
                string ID = item.at(0)->text().toStdString();
                if(item.at(3)->text().toStdString() == me->userID){
                    QMessageBox::information(this, "购买", "不能购买自己的商品！");
                }
                else{
                buyWidget *a = new buyWidget(this, me, ID);
                a->show();
                connect(a, &buyWidget::over, this, [=](){
                   a->hide();
                });
                connect(a, &buyWidget::recharge, this, [=](){
                    emit recharge_btn->release();
                });
                }
            });

        }
//        qDebug()<<"行数为"<<row<<"ID为"<<ID.c_str();
//        QDialog buy_dlg(this);
//        buy_dlg.setFixedSize(240, 300);
//        buy_dlg.setWindowTitle("购买");
//        buy_dlg.setWindowIcon(QIcon(":/res/icon.png"));
//        QPushButton btn1("马上下单", &buy_dlg);
//        btn1.move(35+3, 250);
//        QPushButton btn2("取消订单", &buy_dlg);
//        btn2.move(125+3, 250);
 //       buy_dlg.exec();

    });
    //修改信息按钮
    backButton *change_info_btn = new backButton(":/res/changeButton");
    change_info_btn->hide();
    change_info_btn->setParent(this);
    change_info_btn->move(490, 200);
    connect(change_info_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            change_information_dialog *changeinfo_dlg = new change_information_dialog(this, me);
            changeinfo_dlg->show();
            connect(changeinfo_dlg, &change_information_dialog::save, this, [=](){
                emit ui->actioninformation->triggered();
            });
        });
    });

    //返回按钮
    backButton *back_btn = new backButton(":/res/backButton");
    back_btn->hide();
    back_btn->setParent(this);
    back_btn->move(this->width()*0.8, this->height()*0.85);
    connect(back_btn, &backButton::release, this, [=](){
        QTimer::singleShot(150, this, [=](){
            ui->stackedWidget->setCurrentIndex(0);
            back_btn->hide();
            sou_btn->hide();
            all_btn->hide();
            change_btn->hide();
            search_btn->hide();
            buy_btn->hide();
            change_info_btn->hide();
            recharge_btn->hide();
        });
    });
    ui->buyer_table->setColumnCount(5);              //                                NO                            NO
    ui->buyer_table->setHorizontalHeaderLabels(QStringList()<<"商品ID"<<"名称"<<"价格"<<"卖家ID"<<"上架时间");

    //买家界面
    connect(ui->actionbuyer, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(1);
       back_btn->show();
       change_btn->hide();
       search_btn->hide();
       buy_btn->show();
       change_info_btn->hide();
       recharge_btn->hide();

       int n = 0;
       for(int i = 0;i<Commodity::all.size(); i++){
           if(Commodity::all[i].state != "已下架") n++;
       }
       ui->buyer_table->setRowCount(n);
       n = 0;
       int num = 0;
          //设置正文
       for(int i = 0;i < 8*Commodity::all.size();i++){
           if(i%8 == 3 || i%8 == 7 || i%8 == 4) continue;
           if(Commodity::all[i/8].state == "已下架"){i+=7;continue;}
           QString str = Commodity::Qall[i/8][i%8].c_str();
           QTableWidgetItem *item =  new QTableWidgetItem(str);
           item->setTextAlignment(Qt::AlignCenter);
           ui->buyer_table->setItem(n/5, num % 5, item);
           n++;num++;
       }

       //搜索按钮+全部按钮
       sou_btn->show();
        all_btn->show();
    });

    ui->buyer_order_table->setColumnCount(6);                    //    订单ID,商品ID,交易单价,数量,交易时间,卖家ID
    ui->buyer_order_table->setHorizontalHeaderLabels(QStringList()<<"订单ID"<<"商品ID"<<"交易单价"<<"数量"<<"交易时间"<<"买家ID");
    //已购买订单
    connect(ui->actionbuyer_order, &QAction::triggered, this, [=](){
        back_btn->show();
        all_btn->hide();
        buy_btn->hide();
        change_btn->hide();
        search_btn->hide();
        sou_btn->hide();
        change_info_btn->hide();
        recharge_btn->hide();
       ui->stackedWidget->setCurrentIndex(3);
       string ID = me->userID;
       int n = 0;
       for(int i = 0; i < Order::all.size();i++){
           if(Order::all[i].buyerID == ID) n++;
       }
       ui->buyer_order_table->clearContents();
       ui->buyer_order_table->setRowCount(n);
       int x = 0, y = 0;
       for(int i = 0;i < Order::all.size();i++){
           if(Order::Qall[i][6] != ID) continue;
           for(int j = 0; j<7 ; j++){
               if(j == 6) continue;
               QString str = Order::Qall[i][j].c_str();
               QTableWidgetItem *item = new QTableWidgetItem(str);
               item->setTextAlignment(Qt::AlignCenter);
               ui->buyer_order_table->setItem(x, y % 6, item);
               y++;
           }
           x++;
       }
       if(n == 0){
           QMessageBox::information(this, "订单", "您还没有购买商品", "确认");
       }
    });


    ui->seller_table->setColumnCount(6);
    ui->seller_table->setHorizontalHeaderLabels(QStringList()<<"商品ID"<<"名称"<<"价格"<<"数量"<<"上架时间"<<"商品状态");
    //卖家界面
    connect(ui->actionseller, &QAction::triggered, this, [=](){
        ui->stackedWidget->setCurrentIndex(2);
        back_btn->show();
        all_btn->hide();
        sou_btn->hide();
        change_btn->show();
        search_btn->show();
        buy_btn->hide();
        change_info_btn->hide();
        recharge_btn->hide();

        int n = 0;
        for(int i = 0;i<Commodity::all.size(); i++){
            if(Commodity::all[i].sellerID == me->userID) n++;
        }
        ui->seller_table->setRowCount(n);
        n = 0;
        int num = 0;
           //设置正文 商品ID 名称        价格   数量   上架时间    商品状态
        for(int i = 0;i < 8*Commodity::all.size();i++){
            if(i%8 == 5 || i%8 == 4) continue;
            if(Commodity::all[i/8].sellerID != me->userID){i+=7;continue;}
            QString str = Commodity::Qall[i/8][i%8].c_str();
            QTableWidgetItem *item =  new QTableWidgetItem(str);
            item->setTextAlignment(Qt::AlignCenter);
            ui->seller_table->setItem(n/6, num % 6, item);
            n++;num++;
        }
    });
    //上架商品
    connect(ui->actionon_shelf, &QAction::triggered, this, [=](){
       on_self_dialog *on_shelf = new on_self_dialog(this, me->userID);
       on_shelf->show();
    });

    ui->seller_order_table->setColumnCount(6);                    //    订单ID,商品ID,交易单价,数量,交易时间,卖家ID
    ui->seller_order_table->setHorizontalHeaderLabels(QStringList()<<"订单ID"<<"商品ID"<<"交易单价"<<"数量"<<"交易时间"<<"卖家ID");
    //已购买订单
    connect(ui->actionseller_order, &QAction::triggered, this, [=](){
        back_btn->show();
        all_btn->hide();
        buy_btn->hide();
        change_btn->hide();
        search_btn->hide();
        sou_btn->hide();
        change_info_btn->hide();
        recharge_btn->hide();
       ui->stackedWidget->setCurrentIndex(4);
       string ID = me->userID;
       int n = 0;
       for(int i = 0; i < Order::all.size();i++){
           if(Order::all[i].seller == ID) n++;
       }
       ui->seller_order_table->clearContents();
       ui->seller_order_table->setRowCount(n);
       int x = 0, y = 0;
       for(int i = 0;i < Order::all.size();i++){
           if(Order::Qall[i][5] != ID) continue;
           for(int j = 0; j<7 ; j++){
               if(j == 5) continue;
               QString str = Order::Qall[i][j].c_str();
               QTableWidgetItem *item = new QTableWidgetItem(str);
               item->setTextAlignment(Qt::AlignCenter);
               ui->seller_order_table->setItem(x, y % 6, item);
               y++;
           }
           x++;
       }
       if(n == 0){
           QMessageBox::information(this, "订单", "您还没有售出商品", "确认");
       }
    });

    //信息管理
    connect(ui->actioninformation, &QAction::triggered, this, [=](){
       ui->stackedWidget->setCurrentIndex(5);
       back_btn->show();
       sou_btn->hide();
       all_btn->hide();
       change_btn->hide();
       search_btn->hide();
       buy_btn->hide();
       change_info_btn->show();
       recharge_btn->show();
       //显示信息
       QString a = "用户地址：";
       QString p = "联系方式：";
       QString n = "用户姓名：";
       QString b = "用户余额：";
       a.append(me->adress.c_str());
       p.append(me->phoneNumber.c_str());
       n.append(me->username.c_str());
       b.append(me->balance.c_str());
       QPalette pe;
       pe.setColor(QPalette::WindowText, Qt::white);
       ui->name->setPalette(pe);
       ui->phoneNumber->setPalette(pe);
       ui->adress->setPalette(pe);
       ui->balance->setPalette(pe);
       ui->name->setText(n);
       ui->phoneNumber->setText(p);
       ui->adress->setText(a);
       ui->balance->setText(b);
    });

    //注销操作
    connect(ui->cancellation, &QAction::triggered, this, [=](){
        emit back_btn->release();
        emit userCancellation();
    });
}

userWindow::~userWindow()
{
    delete ui;
}

void userWindow::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/blueBackground.png");
    painter.drawPixmap(0, 0, 960, 540, pix);
}
