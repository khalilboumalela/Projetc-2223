#ifndef EMPLOYES_H
#define EMPLOYES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class employes
{
   QString nom,prenom,sexe,fonction;
   float salaire;
   int cin,tel;
public:
    employes();
    employes(QString,QString,int,QString,int,QString,float);

    ////Getters

    QString Getnom(){return nom;}
    QString Getprenom(){return prenom;}
    QString Getsexe(){return sexe;}
    QString Getfonction(){return fonction;}
    int Getcin(){return cin;}
    int Gettel(){return tel;}
    float Getsalaire(){return salaire;}

    ////Setter

    void setnom(QString n){nom=n;}
    void setprenom(QString n){prenom=n;}
    void setsexe(QString n){sexe=n;}
    void setfonction(QString n){fonction=n;}
    void setcin(int n){cin=n;}
    void settel(int n){tel=n;}
    void setsalaire(float n){salaire=n;}
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer();

#endif // EMPLOYES_H
