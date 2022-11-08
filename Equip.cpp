#include "Equip.h"
#include <QSqlQuery>
#include <QtDebug>
#include <iostream>
#include<QObject>
#include<QSqlQueryModel>
using namespace std;

Equipement::Equipement()
{
    refe=0;
    quant=0;
    nom="";
    prix=0;
    dajout="";
}
Equipement::Equipement(QString nom,int refe,int quant,float prix,QString dajout){
    this->nom=nom;
        this->refe=refe;
        this->quant=quant;
        this->prix=prix;
        this->dajout=dajout;
}
QString Equipement:: getnom () {
    return nom;
}
int Equipement:: getrefe(){
    return refe;
}
int Equipement:: getquant(){
    return quant;
}
float Equipement:: getprix(){
    return prix;
}
QString Equipement:: getdajout() {
    return dajout;
}
void Equipement:: setnom(QString nom){
     this->nom=nom;
}
void Equipement:: setrefe(int refe){
     this->refe=refe;
}
void Equipement:: setquant(int quant){
     this->quant=quant;
}
void Equipement:: setprix(float prix){
     this->prix=prix;
}
void Equipement:: setdajout(QString dajout){
     this->dajout=dajout;
}
bool Equipement:: ajouter(){

    QSqlQuery query;
    QString refe_string=QString::number(refe);
    QString quant_string=QString::number(quant);
    query.prepare("INSERT INTO EQUIPE (NOM,REFE,QUANT,PRIX,DAJOUT) "
                  "VALUES (:forename,:refe,:quant,:prix, :dajout)");
    query.bindValue(":forename", nom);
    query.bindValue(":refe",refe_string);
    query.bindValue(":quant",quant_string);
    query.bindValue(":prix",prix);
    query.bindValue(":dajout", dajout);
   return query.exec();


    //return test;
}
bool Equipement::supprimer(int refe)
{
    QSqlQuery query;
     QString refe_string=QString::number(refe);
    query.prepare("Delete From EQUIPE  where  REFE=:refe ");
    query.bindValue(0, refe_string);
    return query.exec();

}

   QSqlQueryModel* Equipement :: afficher(){
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("select  * from EQUIPE ");
    model->setHeaderData(0, Qt::Horizontal,QObject:: tr("nom"));
    model->setHeaderData(1, Qt::Horizontal,QObject:: tr("refe"));
    model->setHeaderData(2, Qt::Horizontal,QObject:: tr("quant"));
    model->setHeaderData(3, Qt::Horizontal,QObject:: tr("prix"));
    model->setHeaderData(4, Qt::Horizontal,QObject:: tr("dajout"));
    return model;
}
   bool Equipement :: modifier(int refe){

             QSqlQuery query;
             QString refe_string=QString::number(refe);
             QString quant_string=QString::number(quant);

             query.prepare("UPDATE EQUIPE  SET  nom=:forename,refe_string=:refe, quant_string=:quant,prix=:prix,dajout=:dajout where refe=:refe;");

             query.bindValue(":forename", nom);
             query.bindValue(":refe",refe_string);
             query.bindValue(":quant",quant_string);
             query.bindValue(":prix",prix);
             query.bindValue(":dajout", dajout);

            return query.exec();


             //return test;
         }




