#include "application.h"

#include <QUdpSocket>
#include <iostream>
#include <sstream>

#include "model.h"

using std::string;
using std::stringstream;


Application::Application(int &argc, char **argv) : QCoreApplication (argc, argv)
{
    auto socket = std::make_shared<QUdpSocket>(this);
    // TODO: Rewrite to non-const values
    generationModel = std::make_shared<model>(0.5, 0.5, 0.5);
    socket->bind(QHostAddress("127.0.0.1"), static_cast<quint16>(1488));

    server = std::make_shared<Server>(socket);
    generationModel = std::make_shared<model>(1., 2., 3.);
    connect(server.get(), &Server::hasPendingRequests, this, &Application::processStrings);
}

void Application::processStrings(queue<Request> & q)
{
    while (!q.empty())
    {
        Request r = q.front();
        q.pop();
        std::cout << q.size();
        // TODO: Rewrite this
        stringstream requestIn(r.body.toStdString());
        std::string command;
        string response;
        stringstream responseOut(response);

        std::cout << "Request: " << r.body.toStdString() << std::endl;
        requestIn >> command;

        if (command == "change_cashier:")
        {
            int cashierIndex;
            double newMean;
            requestIn >> cashierIndex >> newMean;
            if (cashierIndex == 1)
            {
                generationModel->setFirstCustomerMean(newMean);
            } else if (cashierIndex == 2)
            {
                generationModel->setSecondCustomerMean(newMean);
            }
            responseOut << "change_cashier: done";
        } else if (command == "change_generator:")
        {
            double newMean;
            requestIn >> newMean;
            generationModel->setCustomerGeneratorMean(newMean);
            responseOut << "change_generator: done";

        } else if (command == "start_modeling:")
        {
            std::cout << "Started modeling";
            generationModel->run();
            responseOut << "start_modeling: done";
        } else if (command == "stop_modeling:") {
            generationModel->stop();
            responseOut << "stop_modeling: done";
        } else if (command == "get_statistics:") {
            int cashierIndex;
            requestIn >> cashierIndex;
            responseOut << "get_statistics: " << cashierIndex << " "
                        << generationModel->getMeanValueForCustomer(cashierIndex) << " "
                        << generationModel->getStdValueForCustomer(cashierIndex);
        } else {
            std::cout << "Command unkown!";
        }
        std::cout << "Response: " << responseOut.str() << std::endl;
        server->sendResponse(r.address, responseOut.str());
    }
}

