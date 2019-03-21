#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "modelserverclient.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_connectServerButton_clicked();

    void on_setCustomerMeanButton_clicked();

    void on_setFirstCashierButton_clicked();

    void on_setSecondCashierButton_clicked();

    void on_startModelingButton_clicked();

    void on_stopModelingButton_clicked();

    void on_statsUpdateButton_clicked();

private:
    Ui::MainWindow *ui;
    ModelServerClient client;
};

#endif // MAINWINDOW_H
