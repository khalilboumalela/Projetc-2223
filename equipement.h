#ifndef EQUIPEMENT_H
#define EQUIPEMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDoubleValidator>
#include <QtDebug>
#include <QTableView>
#include <QObject>
#include <QMainWindow>
#include <QDateTime>
#include <QMessageBox>
#include <QDate>

class equipement
{
public:
    equipement();
    equipement(int,QString,int,int,QDate);

    int getreff();
    QString getnom();
    int getquant();
    int getprix();
    QDate getdate();

    void setreff(int);
    void setnom(QString);
    void setquant(int);
    void setprix(int);
    void setdate(QDate);

    bool ajouter();
    bool modifier();
    bool supprimer(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* afficher_reff();
    QSqlQueryModel* tri_reff();
    QSqlQueryModel* tri_nom();
    QSqlQueryModel* tri_quant();

    void clearTable(QTableView * table);
    void chercheReff(QTableView *table, int x);
    void chercheNom(QTableView *table, QString x);



private:
    int REFFERANCE;
    QString NOM;
    int QUANTITE;
    int PRIX;
    QDate DATE_A;
};

#endif // EQUIPEMENT_H
