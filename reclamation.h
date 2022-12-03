#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQueryModel>
#include <QTableView>

class reclamation
{
    public:
    reclamation();
    reclamation(int,QString,QString,int,QString);
    int getid();
    QString getnom();
    QString getprenom();
    int getnumero();
    QString getadresse();
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setnumero(int);
    bool ajouter();
    bool modifier();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
     QSqlQueryModel* tri_id();
     QSqlQueryModel* geo();
     QSqlQueryModel* recherche(QString);

private:
    int id,numero;
    QString nom,prenom,adresse;

};

#endif // EMPLOYE_H
