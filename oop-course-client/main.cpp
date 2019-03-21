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
    return a.exec();
}
