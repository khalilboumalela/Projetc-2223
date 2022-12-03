#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
 db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("Source_Projet2A");
db.setUserName("khalil");//inserer nom de l'utilisateur
db.setPassword("employe");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;

    return  test;
}

void Connection::closeconnection(){db.close();}


bool Connection::CreateConnexion()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("khalil");//inserer nom de l'utilisateur
    db.setPassword("employe");//inserer mot de passe de cet utilisateur


    if (db.open())
        test=true;
    return  test;
}
void Connection::FermerConnexion()
{
    db.close();
}

bool Connection::OuvrirConnexion()
{
    if (db.open())
        return true ;
    else
        return false;

}
