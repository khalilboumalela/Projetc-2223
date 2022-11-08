#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Equip.h"
#include<QDebug>
#include <iostream>
#include <QMessageBox>
#include<QIntValidator>
#include<QSqlQueryModel>
#include<QComboBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
ui->le_refe->setValidator( new QIntValidator(100, 9999999, this));
ui->tab_etudiant->setModel(E1.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{   QString nom =ui->le_nom->text();
    int refe =ui->le_refe->text().toInt();
    int quant =ui->la_quant->text().toInt();
    float prix =ui->le_prix->text().toFloat();
   QString dajout =ui->le_dajout->text();

Equipement E(nom,refe,quant,prix,dajout);
bool test=E.ajouter();
ui->tab_etudiant->setModel(E1.afficher());
if(test)


    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("ajout successful.\n"
                            "ajout effectuer."), QMessageBox::Cancel);


else

    QMessageBox::critical(nullptr, QObject::tr("nope"),
                QObject::tr("connection failed.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
void MainWindow::on_pb_supp_clicked()
{
    QMessageBox msgBox;
Equipement E1;
int refe =ui->le_idsupp->text().toInt();
bool test=E1.supprimer(refe);
if(test)
{
ui->tab_etudiant->setModel(E1.afficher());

    msgBox.setText("supprimer avec succes");

}
else

   msgBox.setText("echec");

msgBox.exec();
}
void MainWindow::on_pb_modifier_clicked()

{  Equipement E1;

    QString nom =ui->le_nom2->text();
    int refe =ui->le_refe2->text().toInt();
    int quant =ui->la_quant2->text().toInt();
    float prix =ui->le_prix2->text().toInt();
    QString dajout=ui->le_dajout2->text();
     Equipement E(nom,refe,quant,prix,dajout);

bool test=E.modifier(refe);

ui->tab_etudiant->setModel(E1.afficher());

if(test)
  {

    QMessageBox::information(nullptr, QObject::tr("SUCCESS"),

                QObject::tr("update successful.\n"

                            "modifaction effectuer."), QMessageBox::Cancel);
}

else
    QMessageBox::critical(nullptr, QObject::tr("ERROR"),

                QObject::tr("connection failed.\n"

                            "Click Cancel to exit."), QMessageBox::Cancel);
}






