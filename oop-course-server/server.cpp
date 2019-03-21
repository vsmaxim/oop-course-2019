#include "server.h"
#include <QString>
#include <QByteArray>

void Server::processDatagram(QByteArray data, SenderAddress source)
{
    pendingRequests.emplace(source, QString::fromUtf8(data.data(), data.size()));
    emit hasPendingRequests(pendingRequests);
}

Server::Server(QObject *parent) : QObject(parent)
{

}

Server::Server(std::shared_ptr<QUdpSocket> socket) : socket(socket)
{
    connect(socket.get(), SIGNAL(readyRead()), this, SLOT(readPendingStrings()));
}

void Server::sendResponse(SenderAddress &address, const std::string &response)
{
    QString r(response.c_str());
    QByteArray bytes = r.toUtf8();
    socket->writeDatagram(bytes, address.address, address.port);
}

void Server::readPendingStrings()
{
    while (socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(static_cast<int>(socket->pendingDatagramSize()));
        SenderAddress address;
        socket->readDatagram(datagram.data(), datagram.size(), &address.address, &address.port);
        processDatagram(datagram, address);
    }
}
