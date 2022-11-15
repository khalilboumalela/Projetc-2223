#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include "emission.h"
#include <QApplication>
#include <QMessageBox>

class Connection
{
    QSqlDatabase db;
public:
    Connection();
    bool createconnection();
    void closeConnection();
};




#endif // CONNECTION_H
