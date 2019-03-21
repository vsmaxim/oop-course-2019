#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QUdpSocket>
#include <memory>
#include <string>

using std::string;
using std::shared_ptr;
using std::make_shared;


class Client : public QObject
{
    Q_OBJECT
private:
    shared_ptr<QUdpSocket> socket;
public:
    explicit Client(QObject *parent = nullptr);
    Client(string host, int port);

    string sendRequest(const string & request, const string & address, const int & port);
signals:

public slots:
};

#endif // CLIENT_H
