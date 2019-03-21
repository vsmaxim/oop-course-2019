#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <string>

using std::string;
using std::stringstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("127.0.0.1", 10003)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectServerButton_clicked()
{
    QStringList serverAddress = ui->serverAddressEdit->text().split(":");
    if (serverAddress.size() != 2)
    {
        return;
    }
    client.setTargetHost(serverAddress[0].toStdString(), serverAddress[1].toInt());
}

void MainWindow::on_setCustomerMeanButton_clicked()
{
    double newMean = ui->meanCustomerTime->value();
    client.changeGeneratorRequest(newMean);
}

void MainWindow::on_setFirstCashierButton_clicked()
{
    double newMean = ui->firstCashierMeanTimeSpin->value();
    client.changeCashierRequest(1, newMean);
}

void MainWindow::on_setSecondCashierButton_clicked()
{
    double newMean = ui->secondCashierMeanTimeSpin->value();
    client.changeCashierRequest(2, newMean);
}

void MainWindow::on_startModelingButton_clicked()
{
    client.startModelingRequest();
}

void MainWindow::on_stopModelingButton_clicked()
{
    client.stopModelingRequest();
}

void MainWindow::on_statsUpdateButton_clicked()
{
    for (size_t i = 1; i <= 2; ++i)
    {
        string stats = client.getStatistics(static_cast<int>(i));
        stringstream response(stats);
        double mean, std;
        string prefix;
        int cashierId;

        response >> prefix >> cashierId >> mean >> std;

        if (i == 1)
        {

        }
        else if ( i == 2)
        {

        }
    }
}
