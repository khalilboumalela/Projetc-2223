#include "employes.h"
#include "connection.h"
#include<QDebug>

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

int employes::supprimer(int cin)
{
    QString Scin=QString::number(cin);


    QSqlQueryModel model;
    QSqlQuery query;
    model.setQuery("SELECT * from EMPLOYE WHERE (CIN LIKE '"+Scin+"');");
    QString Cin=model.data(model.index(0, 2)).toString();
    Cin=model.data(model.index(0, 2)).toString();

    qInfo() << "AA "<<Scin<<endl;
    if (Cin=="")
        return 2;
    else
    {query.prepare("DELETE from EMPLOYE where cin = :id ;");
        query.bindValue(":id",cin);

        return    query.exec();}

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

QSqlQueryModel* employes::rechercher (const QString &aux)
{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from EMPLOYE where ((cin || nom || prenom || fonction || salaire || sexe||tel) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire  "));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction "));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));

    return model;
}


employes employes::modifier(QString cin)
{
    employes E;
    QSqlQueryModel model;
    QSqlQuery query;

    model.setQuery("SELECT * from EMPLOYE WHERE (CIN LIKE '"+cin+"')");
    QString Nom=model.data(model.index(0, 0)).toString();
    QString Prenom=model.data(model.index(0, 1)).toString();
    QString Salaire=model.data(model.index(0,3)).toString();
    QString Cin=model.data(model.index(0, 2)).toString();
    QString Fonction=model.data(model.index(0, 4)).toString();
    QString Tel=model.data(model.index(0, 5)).toString();
    QString Sexe=model.data(model.index(0, 6)).toString();
    /* query.prepare("SELECT * from EMPLOYE WHERE CIN= :CIN");
        query.bindValue(":CIN",cin);*/


    //  qInfo() << "Nom"<<" "<<model.data(model.index(0, 1)).toString()<<endl;

    E.setnom(Nom);
    E.setprenom(Prenom);
    E.setcin(Cin.toInt());
    E.setsalaire(Salaire.toInt());
    E.settel(Tel.toInt());
    E.setfonction(Fonction);
    E.setsexe(Sexe);

    return    E;

}

bool employes::modifier2(QString cin,employes E)
{
    QString Ssalaire;
    Ssalaire=Ssalaire.number(E.Getsalaire());
    QString Stel;
    Stel=Stel.number(E.Gettel());
    QString Scin;
    Scin=Scin.number(E.Getcin());
    QSqlQuery query;

    query.prepare("UPDATE EMPLOYE SET NOM= :nom, PRENOM= :prenom,CIN= :cin2 , SALAIRE= :salaire, FONCTION= :fonction, TEL= :tel ,SEXE= :sexe  where CIN= :cin ;");
    query.bindValue(":cin", cin);
    query.bindValue(":nom",E.Getnom());
    query.bindValue(":prenom", E.Getprenom());
    query.bindValue(":fonction",E.Getfonction());
    query.bindValue(":salaire",Ssalaire);
    query.bindValue(":cin2",Scin);
    query.bindValue(":sexe",E.Getsexe());
    query.bindValue(":tel",Stel);

    return    query.exec();


}
