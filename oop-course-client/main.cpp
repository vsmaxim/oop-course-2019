#include "mainwindow.h"

#include <iostream>
#include <windows.h>
#include <QApplication>
#include <client.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    Client c("127.0.0.1", 10003);
//    c.sendRequest("start_modeling:", "127.0.0.1", 1488);
//    c.sendRequest("change_generator: 5.0", "127.0.0.1", 1488);
//    c.sendRequest("change_cashier: 1 1.0", "127.0.0.1", 1488);
//    c.sendRequest("change_cashier: 2 10.0", "127.0.0.1", 1488);
//    Sleep(10000);
//    std::cout << c.sendRequest("get_statistics: 1")
//    c.sendRequest("stop_modeling:", "127.0.0.1", 1488);
    return a.exec();
}
