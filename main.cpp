#include "mainwindow.h"
#include"CMD.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    CMD::init();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
