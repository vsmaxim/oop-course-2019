#include "modelserverclient.h"
#include <sstream>
#include <string>
#include <iostream>
#include <QDebug>

using std::stringstream;


ModelServerClient::ModelServerClient(std::string host, int port, std::string targetHost, int targetPort) : Client (host, port),
    targetHost(host), targetPort(port)
{

}

ModelServerClient::ModelServerClient(std::string host, int port) : Client(host, port), targetHost(), targetPort()
{

}


void ModelServerClient::setTargetHost(string host, int port)
{
    targetHost = host;
    targetPort = port;
}

std::string ModelServerClient::sendRequest(const std::string &request)
{
    return Client::sendRequest(request, targetHost, targetPort);
}

string ModelServerClient::getStatistics(int cashierId)
{
    stringstream r;
    r << "get_statistics: " << cashierId;
    qDebug() << QString(r.str().c_str());
    return sendRequest(r.str());
}

string ModelServerClient::changeCashierRequest(int cashierId, double newMean)
{
    stringstream r;
    r << "change_cashier: " << cashierId << " " << newMean;
    qDebug() << QString(r.str().c_str());
    return sendRequest(r.str());
}


string ModelServerClient::changeGeneratorRequest(double newMean)
{
    stringstream r;
    r << "change_generator: " << newMean;
    qDebug() << QString(r.str().c_str());
    return sendRequest(r.str());
}


string ModelServerClient::startModelingRequest()
{
    return sendRequest("start_modeling: ");
}


string ModelServerClient::stopModelingRequest()
{
    return sendRequest("stop_modeling: ");
}
