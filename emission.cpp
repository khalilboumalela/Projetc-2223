#include "emission.h"
#include <QSqlQuery>
#include <QDebug>
#include <QSqlQueryModel>
#include <QObject>

emission::emission()
{
ID=0;NOM="";DATED="";DATEF="";
}


emission::emission(int ID){this->ID=ID;};

emission::emission(int ID,QString NOM,QString DATED,QString DATEF)
{
this->ID=ID;
this->NOM=NOM;
this->DATED=DATED;
this->DATEF=DATEF;
}

int emission::getId(){return ID;}
QString emission::getNom(){return NOM;}
QString emission::getDated(){return DATED;}
QString emission::getDatef(){return DATEF;}

void emission::setId(int ID){this->ID=ID;}
void emission::setNom(QString NOM){this->NOM=NOM;}
void emission::setDated(QString DATED){this->DATED=DATED;}
void emission::setDatef(QString DATEF) {this->DATEF=DATEF;}



QSqlQueryModel* emission::afficher()
{
     QSqlQueryModel* model=new  QSqlQueryModel();

     model->setQuery("SELECT* FROM EMISSION");

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATED"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEF "));

    return model;

}

bool emission::ajouter()
{
    QString ID_string= QString::number(ID);
    bool test=false;
    QSqlQuery query;
      query.prepare("INSERT INTO EMISSION (ID, NOM,DATED,DATEF) "
                    "VALUES (:ID, :NOM, :DATED,:DATEF)");
      query.bindValue(0,ID_string);
      query.bindValue(1,NOM);
      query.bindValue(2,DATED);
      query.bindValue(3,DATEF);
      query.exec();
      test =true;
    return test ;
}



bool emission::supprimer(int ID)
{
 QSqlQuery query;
 QString id= QString::number(ID);

 query.prepare("Delete from EMISSION where ID= :ID");
 query.bindValue(":ID",id);
 return query.exec();
}


bool emission::modifier()
{
    bool test=false;
    QSqlQuery query;

    QString Id= QString::number(ID);

      query.prepare("UPDATE EMISSION set ID=:ID , NOM=:NOM, DATED=:DATED , DATEF=:DATEF   WHERE ID=:ID");

      query.bindValue(":ID",Id);
      query.bindValue(":NOM",NOM);
      query.bindValue(":DATED",DATED);
      query.bindValue(":DATEF",DATEF);

     if( query.exec())
        test =true;


    return test ;
}

QSqlQueryModel * emission::afficher_tri_nom()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from EMISSION order by NOM asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATED"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEF"));



    return model;
}
QSqlQueryModel * emission::afficher_tri_dated()
{QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from EMISSION order by DATED asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATED"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEF"));



    return model;
}
QSqlQueryModel * emission::afficher_tri_datef()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from EMISSION order by DATEF asc ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATED"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEF"));



    return model;
}

QSqlQueryModel* emission::chercher_emission(QString text){

//
    QSqlQuery query;
    QSqlQueryModel* model=new QSqlQueryModel();
   {

     model->setQuery("SELECT * FROM EMISSION where ID like '"+text+"'");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("DATED"));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("DATEF"));
     }

    return model;

}
