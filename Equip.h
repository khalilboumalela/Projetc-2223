#ifndef EQUIP_H
#define EQUIP_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQueryModel>
class Equipement
{
public:
    Equipement();
    Equipement(QString,int,int,float,QString);
    QString getnom();
    int getrefe();
    int getquant();
    float getprix();
    QString getdajout();
    void setnom(QString);
    void setrefe(int);
    void setquant(int);
    void setprix(float);
    void setdajout(QString);

    bool ajouter();
    bool test/*=false*/;
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int refe);

    QSqlQueryModel*  tester();
private :
    int refe,quant;
    float prix;
    QString nom,dajout;
};

#endif //  EQUIP_H
