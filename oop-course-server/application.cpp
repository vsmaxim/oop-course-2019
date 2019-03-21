#include "application.h"

#include <QUdpSocket>
#include <iostream>
#include <sstream>

#include "model.h"


Application::Application(int &argc, char **argv) : QCoreApplication (argc, argv)
{
    auto socket = std::make_shared<QUdpSocket>(this);
    generationModel = std::make_shared<Model>(0.5, CASHIER_DEFAULTS);
    socket->bind(QHostAddress("127.0.0.1"), static_cast<quint16>(1488));

    server = std::make_shared<Server>(socket);
    connect(server.get(), &Server::hasPendingRequests, this, &Application::processStrings);
}


std::string Application::stopModeling(std::stringstream &in)
{
    generationModel->stop();
    return "stop_modeling: done";
}


std::string Application::startModeling(std::stringstream &in)
{
    generationModel->run();
    return "start_modeling: done";
}


std::string Application::changeCashier(std::stringstream &in)
{
    size_t cashierIndex;
    double newMean;
    in >> cashierIndex >> newMean;
    std::cout << "Cashier index to set: " << cashierIndex << std::endl;
    generationModel->setCashierMean(cashierIndex, newMean);
    return "change_cashier: done";
}


std::string Application::changeCustomerGenerator(std::stringstream &in)
{
    double newMean;
    in >> newMean;
    generationModel->setCustomerGeneratorMean(newMean);
    return "change_customer: done";
}


std::string Application::getStatistics(std::stringstream &in)
{
    size_t cashierIndex;
    std::stringstream s;
    in >> cashierIndex;
    s << "get_statistics: " << cashierIndex << " "
      << generationModel->getMeanValueForCustomer(cashierIndex) << " "
      << generationModel->getStdValueForCustomer(cashierIndex);
    return s.str();
}

void Application::processStrings(queue<Request> & q)
{
    while (!q.empty())
    {
        Request r = q.front();
        q.pop();

        std::stringstream requestIn(r.body.toStdString());
        std::string response;
        std::string command;

        std::cout << "Request: " << r.body.toStdString() << std::endl;
        requestIn >> command;

        if (command == "change_cashier:") {
            response = changeCashier(requestIn);
        } else if (command == "change_generator:") {
            response = changeCustomerGenerator(requestIn);
        } else if (command == "start_modeling:") {
            response = startModeling(requestIn);
        } else if (command == "stop_modeling:") {
            response = stopModeling(requestIn);
        } else if (command == "get_statistics:") {
            response = getStatistics(requestIn);
        } else {
            response = "Command unknown!";
        }
        std::cout << response << std::endl;
        server->sendResponse(r.address, response);
    }
}

