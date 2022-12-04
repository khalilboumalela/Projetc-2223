#include "sponsor.h"
#include<QObject>
#include<QMessageBox>
#include <QSqlQuery>
#include <QtDebug>
#include<QSqlRecord>
//#include<QSqlTableModel>
#include<QSqlQueryModel>
Sponsor::Sponsor()
{
     nom=" ";localisation=" ";numtel=0; code=0; email=" " ;
    }

    Sponsor::Sponsor( QString nom,QString localisation,int numtel,int code,QString email)
    {this->nom=nom;this->localisation=localisation;this->numtel=numtel;this->code=code; this->email=email;}
    QString Sponsor::getnom(){return nom;}
    QString Sponsor::getlocalisation(){return localisation;}
     int Sponsor::getnumtel() {return numtel;}
    int Sponsor::getcode(){return code;}

    QString Sponsor::getemail(){return email;}



    void Sponsor::setnom(QString nom){this->nom=nom;}
    void Sponsor::setlocalisation(QString localisation){this->localisation=localisation;}
        void Sponsor::setnumtel(int numtel){this->numtel=numtel;}
    void Sponsor::setcode(int code){this->code=code;}
    void Sponsor::setemail(QString email){this->email=email;}


    bool Sponsor::ajouter()
    {
        QSqlQuery query;
        QString code_string =QString::number(code);
        QString numtel_string =QString::number(numtel);

              query.prepare("INSERT INTO sponsor (NOM,LOCALISATION,NUMTEL,CODE, EMAIL) "
                            "VALUES (:NOM,:LOCALISATION ,:NUMTEL, :CODE, :EMAIL)");

              query.bindValue(":NOM", nom);
              query.bindValue(":LOCALISATION",localisation);
              query.bindValue(":NUMTEL",numtel_string);

              query.bindValue(":CODE",code_string);

              query.bindValue(":EMAIL", email);

          return query.exec();


}

    bool Sponsor::supprimer(int code)
    {

        QSqlQuery query;
    QString res =QString::number(code);
                  query.prepare("Delete from Sponsor where CODE=:CODE");
                  query.bindValue(":CODE",res);

              return query.exec();


    }

    QSqlQueryModel * Sponsor::afficher()
           {
        QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("SELECT * FROM SPONSOR;");
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("LOCALISATION"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMTEL"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("RES"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));

        return model;

           }
    QSqlQueryModel * Sponsor::afficher1()
           {
        QSqlQueryModel * model=new QSqlQueryModel();

      model->setQuery("select * from Sponsor where  code = "+QString::number(code) );
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("LOCALISATION"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMTEL"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("RES"));
     model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));

        return model;

           }
    
    bool Sponsor::recherche(int code)
    {
        QSqlQuery q("select * from Sponsor where  code = "+QString::number(code) );
                 QSqlRecord rec = q.record();

                 qDebug() << "Number of columns: " << rec.count();

                 int nameCol = rec.indexOf("CODE"); // index of the field "name"
                 while (q.next()){

                     qDebug() << q.value(nameCol).toString();
                     QString a= q.value(nameCol).toString();
                     if(a!=""){

                           return true;

           }
           }
                   return false;  }



    
        QSqlQueryModel * Sponsor::tri_code()
       {
            QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from Sponsor order by CODE");

            model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("LOCALISATION"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMTEL"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("RES"));
           model->setHeaderData(5,Qt::Horizontal,QObject::tr("EMAIL"));
           return model;


}
