#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <sstream>
#include <string>
#include <windows.h>
#include <regex>


void MainWindow::updateStatistics()
{
    while (runModeling)
    {
        for (size_t i = 0; i <= 1; ++i)
        {
            string stats = client.getStatistics(static_cast<int>(i));
            std::stringstream response(stats);

            double mean, std;
            string prefix;
            int cashierId;

            response >> prefix >> cashierId >> mean >> std;

            // Temporary hack
            mean /= 1000;
            std /= 1000;

            if (i == 0)
            {
                ui->firstMeanValue->setText(QString::fromStdString(std::to_string(mean)));
                ui->firstSTDValue->setText(QString::fromStdString(std::to_string(std)));
            }
            else if (i == 1)
            {
                ui->secondMeanValue->setText(QString::fromStdString(std::to_string(mean)));
                ui->secondSTDValue->setText(QString::fromStdString(std::to_string(std)));
            }
        }
        Sleep(1000);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client("127.0.0.1", 10003),
    runModeling(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_connectServerButton_clicked()
{
    static std::regex ipPattern("([\\d]{1,3}\\.){3}[\\d]{1,3}:[\\d]{1,5}");

    if (std::regex_match(ui->serverAddressEdit->text().toStdString(), ipPattern))
    {
        QStringList serverAddress = ui->serverAddressEdit->text().split(":");
        client.setTargetHost(serverAddress[0].toStdString(), serverAddress[1].toInt());

        ui->setCustomerMeanButton->setEnabled(true);
        ui->setFirstCashierButton->setEnabled(true);
        ui->setSecondCashierButton->setEnabled(true);
    }
}

void MainWindow::on_setCustomerMeanButton_clicked()
{
    double newMean = ui->meanCustomerTime->value();
    client.changeGeneratorRequest(newMean);
}

void MainWindow::on_setFirstCashierButton_clicked()
{
    double newMean = ui->firstCashierMeanTimeSpin->value();
    client.changeCashierRequest(0, newMean);
}

void MainWindow::on_setSecondCashierButton_clicked()
{
    double newMean = ui->secondCashierMeanTimeSpin->value();
    client.changeCashierRequest(1, newMean);
}

void MainWindow::on_startModelingButton_clicked()
{
    client.startModelingRequest();
    ui->startModelingButton->setEnabled(false);
    ui->stopModelingButton->setEnabled(true);
    runModeling = true;
    statisticsUpdateThread = std::make_shared<std::thread>(&MainWindow::updateStatistics, this);
}

void MainWindow::on_stopModelingButton_clicked()
{
    client.stopModelingRequest();
    ui->startModelingButton->setEnabled(true);
    ui->stopModelingButton->setEnabled(false);
    runModeling = false;
    statisticsUpdateThread->join();
}

void MainWindow::on_statsUpdateButton_clicked()
{

}
