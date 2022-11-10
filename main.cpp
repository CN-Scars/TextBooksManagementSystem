#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("教材管理系统 V1.0");   //改主窗口名字
    w.setWindowFlags(w.windowFlags() &~ Qt::WindowMaximizeButtonHint);  //禁止最大化
    w.show();
    return a.exec();
}
