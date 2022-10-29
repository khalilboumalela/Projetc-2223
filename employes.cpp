#include "employes.h"
#include "connection.h"
employes::employes()
{

}

employes::employes(QString nom,QString prenom,int cin,QString sexe,int tel,QString fonction,float salaire=0)
{
    this->nom=nom;
    this->prenom=prenom;
    this->cin=cin;
    this->sexe=sexe;
    this->tel=tel;
    this->fonction=fonction;
    this->salaire=salaire;
}

bool employes::ajouter()
{Connection c;
   //  bool test=c.createconnect();
    QSqlQuery query;
    QString scin=QString::number(cin) ;
    QString stel=QString::number(tel) ;
    QString ssalaire=QString::number(salaire) ;



    query.prepare("insert into EMPLOYE(NOM,PRENOM,CIN,SALAIRE,FONCTION,TEL,SEXE)" "values (:NOM, :PRENOM, :CIN, :SALAIRE, :FONCTION, :TEL, :SEXE);");


    query.bindValue(":NOM",nom);
    query.bindValue(":PRENOM",prenom);
    query.bindValue(":CIN",scin);
    query.bindValue(":SALAIRE",ssalaire);
    query.bindValue(":FONCTION",fonction);
    query.bindValue(":TEL",tel);
    query.bindValue(":SEXE",sexe);

return query.exec() //&& test
        ;


}

bool employes::supprimer(int cin)
{

    QSqlQuery query;
    query.prepare("DELETE from EMPLOYE where cin = :id ;");
    query.bindValue(":id",cin);
    return    query.exec();

}


QSqlQueryModel * employes::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("SELECT * from EMPLOYE");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SALAIRE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("FONCTION"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("SEXE"));


return model;

}


bool employes::modifier(QString, QString, int, QString, int, QString, float)
{
    QSqlQuery query;

        query.prepare("UPDATE EMPLOYE SET NOM= :NOM,PRENOM= :PRENOM,SALAIRE= :SALAIRE, FONCTION= :FONCTION,TEL= :TEL,  SEXE= :SEXE    where CIN= :CIN ;");
        query.bindValue(":CIN", cin);
         query.bindValue(":NOM",nom);
        query.bindValue(":PRENOM", prenom);
        query.bindValue(":FONCTION",fonction);
        query.bindValue(":SALAIRE",salaire);
        query.bindValue(":SEXE",sexe);
        query.bindValue(":TEL",tel);

                return    query.exec();



}
