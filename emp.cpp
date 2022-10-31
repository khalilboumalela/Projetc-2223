#include "emp.h"
#include "ui_emp.h"
#include "employes.h"
#include <QMessageBox>

Emp::Emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emp)
{
    ui->setupUi(this);
    ui->l_CIN->setValidator(new QIntValidator(0,999999999,this));
       ui->l_tel->setValidator(new QIntValidator(0,99999999,this));
       ui->l_salaire->setValidator(new QIntValidator(0,999999999,this));
       ui->tab_etud->setModel(e.afficher());
}

Emp::~Emp()
{
    delete ui;
}

void Emp::on_ajouter_clicked()
{employes E;
ui->tab_etud->setModel(e.afficher());
    QString prenom=ui->l_prenom->text(), nom=ui->l_nom->text(),fonction=ui->l_Fonction->currentText(),sexe=ui->l_sexe->currentText();
    float salaire=ui->l_salaire->text().toFloat();

    int cin=ui->l_CIN->text().toInt();
    int tel=ui->l_tel->text().toInt();
E.settel(tel);
    E.setnom(nom);
    E.setprenom(prenom);
    E.setcin(cin);
    E.setsalaire(salaire);
    E.setsexe(sexe);
    E.setfonction(fonction);
    bool test=E.ajouter();
    if (test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),
                            QObject::tr("Ajout effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);}


            else
                QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                            QObject::tr("Ajout non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);



}

void Emp::on_supprimer_clicked()
{
    int cin=ui->l_CIN_2->text().toInt();
    bool test=e.supprimer(cin);
    if (test)
    {       ui->tab_etud->setModel(e.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Supression effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}


                    else
                        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                    QObject::tr("Suppression non effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}



void Emp::on_modifier_2_clicked()
{

    employes E;
   E= E.modifier(ui->l_CIN_3->text());
QString Scin=QString::number(E.Getcin());
QString Ssalaire=QString::number(E.Getsalaire());
QString Stel=QString::number(E.Gettel());
       ui->l_CIN->setText(Scin);
       ui->l_nom->setText(E.Getnom());
       ui->l_prenom->setText(E.Getprenom());
       ui->l_Fonction->setCurrentText(E.Getfonction());
       ui->l_sexe->setCurrentText(E.Getsexe());
       ui->l_salaire->setText(Ssalaire);
       ui->l_tel->setText(Stel);

}



void Emp::on_modifier_clicked()
{
    employes E;
    ui->tab_etud->setModel(e.afficher());
    QString prenom=ui->l_prenom->text(), nom=ui->l_nom->text(),fonction=ui->l_Fonction->currentText(),sexe=ui->l_sexe->currentText();
    float salaire=ui->l_salaire->text().toFloat();

    int cin=ui->l_CIN->text().toInt();
    int tel=ui->l_tel->text().toInt();
    E.settel(tel);
        E.setnom(nom);
        E.setprenom(prenom);
        E.setcin(cin);
        E.setsalaire(salaire);
        E.setsexe(sexe);
        E.setfonction(fonction);
    bool test=E.modifier2(ui->l_CIN_3->text(),E);

    if (test)
    {       ui->tab_etud->setModel(E.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Modification effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}


                    else
                        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                    QObject::tr("Modification non effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);

}
