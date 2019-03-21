#ifndef APPLICATION_H
#define APPLICATION_H
#include <QCoreApplication>
#include <memory>
#include <queue>

#include "server.h"
#include "model.h"

using std::shared_ptr;
using std::unique_ptr;
using std::queue;

class Application : public QCoreApplication
{
Q_OBJECT

private:
    shared_ptr<Server> server;
    shared_ptr<model> generationModel;
public:
    Application(int & argc, char ** argv);
    Application(shared_ptr<Server> server);
signals:

public slots:
    void processStrings(queue<Request> & q);

};

#endif // APPLICATION_H
