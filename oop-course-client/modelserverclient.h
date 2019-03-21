#ifndef MODELSERVERCLIENT_H
#define MODELSERVERCLIENT_H

#include <string>
#include <memory>

#include "client.h"

using std::string;

class ModelServerClient : public Client
{
private:
    string targetHost;
    int targetPort;
public:
    ModelServerClient(string host, int port, string targetHost, int targetPort);
    ModelServerClient(string host, int port);

    void setTargetHost(string host, int port);
    string sendRequest(const string & request);


    string changeCashierRequest(int cashierId, double newMean);
    string changeGeneratorRequest(double newMean);
    string startModelingRequest();
    string stopModelingRequest();
    string getStatistics(int cashierId);
};

#endif // MODELSERVERCLIENT_H
