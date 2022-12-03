#include "reclamation.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQuery>
#include <QtDebug>
#include <QString>
#include<QtDebug>
#include<QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include<QDateTime>
#include"QDate"
#include <QTime>
#include <QTimer>
#include <QSqlQueryModel>
#include <QtGui/QIntValidator>
#include<QIntValidator>
#include<QMessageBox>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>
#include "connection.h"
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDoubleValidator>
#include<QtDebug>
#include<QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

#include <QTabWidget>
#include <QTableWidgetItem>
#include <QtDebug>
#include <QIntValidator>
#include <QMessageBox>
#include <QDate>
#include <QTextDocument>
#include "QtPrintSupport"


reclamation::reclamation()
{
id=0; nom="";prenom="";numero=0;adresse="";
}

reclamation::reclamation(int id,QString nom,QString prenom,int numero,QString adresse)
{this->id=id; this->nom=nom; this->prenom=prenom;this->numero=numero;this->adresse=adresse;}
int reclamation::getid(){return id;}
QString reclamation::getnom(){return nom;}
QString reclamation::getprenom(){return prenom;}
int reclamation::getnumero(){return numero;}
QString reclamation::getadresse(){return adresse;}
void reclamation::setid(int id){this->id=id;}
void reclamation::setnom(QString nom){this->nom=nom;}
void reclamation::setprenom(QString prenom){this->prenom=prenom;}
void reclamation::setnumero(int numero){this->numero=numero;}
void reclamation::setadresse(QString adresse){this->adresse=adresse;}
bool reclamation::ajouter()
{
    QString id_string=QString::number(id);
    QSqlQuery query;

          query.prepare("INSERT INTO RECLAMATION(id,nom,prenom,numero,adresse) "
                        "VALUES (:id, :forename, :surname, :number , :location)");
          query.bindValue(0, id_string);
          query.bindValue(1, nom);
          query.bindValue(2, prenom);
          query.bindValue(3, numero);
          query.bindValue(4, adresse);



          return query.exec();


}
bool reclamation::modifier()
{

    QString id_string=QString::number(id);
    QSqlQuery query;

          query.prepare("UPDATE RECLAMATION SET ID=:id, NOM=:forename, PRENOM=:surname, NUMERO=:number , ADRESSE=:location WHERE ID=:id");
          query.bindValue(":id", this->getid());
          query.bindValue(":forename", this->getnom());
          query.bindValue(":surname", this->getprenom());
          query.bindValue(":number", this->getnumero());
          query.bindValue(":location",this->getadresse());
          return query.exec();



}
bool reclamation::supprimer(int id)
{
    QSqlQuery query;

          query.prepare("Delete from reclamation where id=:id");
          query.bindValue(0, id);


          return query.exec();


}

QSqlQueryModel* reclamation::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();

        model->setQuery("SELECT* FROM RECLAMATION;");
        model->setHeaderData(0, Qt::Horizontal,QObject::tr("Identifiant"));
        model->setHeaderData(1, Qt::Horizontal,QObject::tr("Nom"));
        model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
        model->setHeaderData(3, Qt::Horizontal,QObject::tr("Numero"));
        model->setHeaderData(4, Qt::Horizontal,QObject::tr("Adresse"));


        return model;

}


QSqlQueryModel *reclamation::tri_id()
    {
        QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from RECLAMATION order by ID");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));

   return model;
    }




QSqlQueryModel * reclamation::geo()
{
    QString link="https://www.google.com/search?rlz=1C1GCEA_enTN967TN967&tbs=lf:1,lf_ui:1&tbm=lcl&sxsrf=ALiCzsbte0ID6_9W55uqXyzKUm0w0l119A:1670002134638&q=radio+dans+la+tunisie+location&rflfq=1&num=10&ved=2ahUKEwiskongutv7AhWSzoUKHdnECQcQtgN6BAgNEAY#rlfi=hd:;si:,37.026738012970625,10.604027460156233;mv:[[37.177670299999996,10.3654336],[36.7644709,9.760468]]";
    QDesktopServices::openUrl(link);}

QSqlQueryModel* reclamation::recherche(QString recherche){

    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("select * from RECLAMATION WHERE ID LIKE '"+recherche+"%'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("PRENOM"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("NUMERO"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("ADRESSE"));

   return model;

                                                        }
