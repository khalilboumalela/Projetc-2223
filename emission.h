
#ifndef EMISSION_H
#define EMISSION_H
#include <QString>
#include <QSqlQueryModel>



class emission
{
    //atr
private:
       int ID;
       QString NOM;
       QString DATED;
       QString DATEF;
    //cnstr
   public:
    emission();
    emission(int);
    emission(int,QString,QString,QString);

    int getId();
    QString getNom();
    QString getDated();
    QString getDatef();

    void setId(int);
    void setNom(QString);
    void setDated(QString);
    void setDatef(QString);

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);
    bool modifier();

    QSqlQueryModel *afficher_tri_nom();
    QSqlQueryModel * afficher_tri_dated();
    QSqlQueryModel * afficher_tri_datef();
    QSqlQueryModel* chercher_emission(QString text);






};

#endif // EMISSION_H
