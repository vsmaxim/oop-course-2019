#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QtGlobal>
#include <QString>
#include <queue>
#include <memory>

using std::queue;
using std::shared_ptr;

struct SenderAddress
{
    QHostAddress address;
    quint16 port;
};

struct Request
{
    SenderAddress address;
    QString body;

    Request(SenderAddress address, QString body) : address(address), body(body)
    {

    }
};


class Server : public QObject
{
    Q_OBJECT

private:
    shared_ptr<QUdpSocket> socket;
    queue<Request> pendingRequests;

    void processDatagram(QByteArray data, SenderAddress source);

public:
    explicit Server(QObject *parent = nullptr);
    Server(shared_ptr<QUdpSocket> socket);

    void sendResponse(SenderAddress & address, const std::string & response);

signals:
    void hasPendingRequests(queue<Request> & requestQueue);

public slots:
    void readPendingStrings();
};

#endif // SERVER_H
