#ifndef SPONSOR_H
#define SPONSOR_H
#include<QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Sponsor
{
public:
    Sponsor();

   Sponsor(QString ,QString,int,int,QString);


        QString getnom();
        QString getlocalisation();
        int getnumtel();
        int getcode();
          QString getemail();


        void setnom(QString);
        void setlocalisation(QString);
          void setnumtel(int);
          void setcode(int);
        void setemail(QString);


        bool ajouter();
        QSqlQueryModel *afficher();
        QSqlQueryModel * afficher1();
        bool supprimer(int);


bool recherche(int code);
bool  tri ();
QSqlQueryModel *tri_code();

    private:
QString nom,localisation,email;
        int code,numtel;



};

#endif // SPONSOR_H
