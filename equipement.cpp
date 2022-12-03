#include "equipement.h"
#include <QtDebug>
#include <QObject>
#include <QMainWindow>
#include <QMessageBox>
#include <QDateTime>
#include <QDate>


equipement::equipement()
{
    REFFERANCE=0;
    NOM=" ";
    QUANTITE=0;
    PRIX=0;
 }
equipement::equipement(int REFFERANCE, QString NOM, int QUANTITE, int PRIX, QDate DATE_A)
{
    this->REFFERANCE=REFFERANCE;
    this->NOM=NOM;
    this->QUANTITE=QUANTITE;
    this->PRIX=PRIX;
    this->DATE_A=DATE_A;
}


int equipement::getreff()
{
    return REFFERANCE;
}
QString equipement::getnom()
{
    return NOM;
}
int equipement::getquant()
{
    return QUANTITE;
}
int equipement::getprix()
{
    return PRIX;
}
QDate equipement::getdate()
{
    return DATE_A;
}

void equipement::setreff(int REFFERANCE)
{
    this->REFFERANCE=REFFERANCE;
}
void equipement::setnom(QString NOM)
{
    this->NOM=NOM;
}
void equipement::setquant(int QUANTITE)
{
    this->QUANTITE=QUANTITE;
}
void equipement::setprix(int PRIX)
{
    this->PRIX=PRIX;
}
void equipement::setdate(QDate DATE_A)
{
    this->DATE_A=DATE_A;
}

bool equipement::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(REFFERANCE);
         query.prepare("INSERT INTO EQUIPEMENT(REFFERANCE,NOM,QUANTITE,PRIX,DATE_A)" "VALUES (:REFFERANCE,:NOM,:QUANTITE,:PRIX,:DATE_A)");
         query.bindValue(":REFFERANCE", REFFERANCE);
         query.bindValue(":NOM", NOM);
         query.bindValue(":QUANTITE", QUANTITE);
         query.bindValue(":PRIX", PRIX);
         query.bindValue(":DATE_A", DATE_A);
    return query.exec();
}
bool equipement::supprimer(int REFFERANCE)
{
    QSqlQuery query;
         query.prepare("DELETE FROM EQUIPEMENT where REFFERANCE= :REFFERANCE");
         query.bindValue(0, REFFERANCE);
    return query.exec();
}
bool equipement::modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE EQUIPEMENT SET NOM=:NOM, QUANTITE=:QUANTITE, PRIX=:PRIX, DATE_A=:DATE_A WHERE REFFERANCE=:REFFERANCE ");
        query.bindValue(":REFFERANCE", REFFERANCE);
        query.bindValue(":NOM", NOM);
        query.bindValue(":QUANTITE", QUANTITE);
        query.bindValue(":PRIX", PRIX);
        query.bindValue(":DATE_A", DATE_A);
    return query.exec();
}

QSqlQueryModel * equipement::tri_reff()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("SELECT * from EQUIPEMENT order by REFFERANCE");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFFERANCE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_A"));
    return model;
}
QSqlQueryModel * equipement::tri_nom()
{
    QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select * from EQUIPEMENT order by NOM");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFFERANCE"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_A"));
    return model;
}
QSqlQueryModel * equipement::tri_quant()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from EQUIPEMENT order by QUANTITE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFFERANCE"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_A"));
    return model;
}

QSqlQueryModel* equipement::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM EQUIPEMENT");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("REFFERANCE"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("QUANTITE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("PRIX"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("DATE_A"));
    return  model;
}
QSqlQueryModel* equipement ::afficher_reff() // ComboBox.
{
    QSqlQueryModel* model=new QSqlQueryModel();
        model->setQuery("SELECT REFFERANCE from EQUIPEMENT");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("REFFERANCE"));
    return model;
}

void equipement::clearTable(QTableView *table)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->clear();
    table->setModel(model);
}


void equipement::chercheReff(QTableView *table, int x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from EQUIPEMENT where regexp_like(REFFERANCE,:REFFERANCE);");
   query->bindValue(":REFFERANCE",x);
   if(x==0)
   {
       query->prepare("select * from EQUIPEMENT;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
void equipement::chercheNom(QTableView *table, QString x)
{
   QSqlQueryModel *model=new QSqlQueryModel();
   QSqlQuery *query =new QSqlQuery;
   query->prepare("select * from EQUIPEMENT where regexp_like(NOM,:NOM);");
   query->bindValue(":NOM",x);
   if(x==0)
   {
       query->prepare("select * from EQUIPEMENT;");
   }
   query->exec();
   model->setQuery(*query);
   table->setModel(model);
   table->show();
}
