#ifndef APPLICATION_H
#define APPLICATION_H
#include <QCoreApplication>

#include <sstream>
#include <memory>
#include <queue>
#include <vector>

#include "server.h"
#include "model.h"

using std::shared_ptr;
using std::unique_ptr;
using std::queue;

const std::vector<double> CASHIER_DEFAULTS{0.5, 0.5};

class Application : public QCoreApplication
{
Q_OBJECT

private:
    shared_ptr<Server> server;
    shared_ptr<Model> generationModel;
public:
    Application(int & argc, char ** argv);
    Application(shared_ptr<Server> server);

    std::string changeCashier(std::stringstream & in);
    std::string changeCustomerGenerator(std::stringstream & in);
    std::string startModeling(std::stringstream & in);
    std::string stopModeling(std::stringstream & in);
    std::string getStatistics(std::stringstream & in);

signals:

public slots:
    void processStrings(queue<Request> & q);

};

#endif // APPLICATION_H
