#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtDebug>
class Connection
{
public:
    QSqlDatabase db;
    Connection();
    bool createconnect();
    void closeconnection();
    bool CreateConnexion();
    bool OuvrirConnexion();
    void FermerConnexion();
};

#endif // CONNECTION_H
