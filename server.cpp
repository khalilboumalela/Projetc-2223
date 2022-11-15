#include <QtNetwork>

#include "server.h"

Server::Server(QObject *parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Connection *connection = new Connection(this);
    connection->setsocketDescriptor(socketDescriptor);
    emit newConnection(connection);
}
