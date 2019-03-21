#include "client.h"

#include <QtGlobal>

Client::Client(QObject *parent) : QObject(parent)
{

}

Client::Client(std::string host, int port)
{
    socket = make_shared<QUdpSocket>(this);
    socket->bind(QHostAddress(host.c_str()), static_cast<quint16>(port));
}

std::string Client::sendRequest(const std::string &request, const std::string &address, const int &port)
{
    QByteArray bytes = QString(request.c_str()).toUtf8();
    socket->writeDatagram(bytes, QHostAddress(address.c_str()), static_cast<quint16>(port));

    while (!socket->waitForReadyRead(1000)) {}

    QByteArray response(static_cast<int>(socket->pendingDatagramSize()), '\0');
    socket->readDatagram(response.data(), response.size());
    return QString::fromUtf8(response).toStdString();
}


