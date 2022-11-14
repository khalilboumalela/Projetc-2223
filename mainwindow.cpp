#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emp.h"
#include <QMessageBox>
#include "connection.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "forgot.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_seconnecter_clicked()
{Emp e;
    Connection c;

    int tst=0; tst++;
    QString Name,Mdp;

    c.createconnect();
    QSqlQueryModel model;

    model.setQuery("SELECT * from INF_CONNEXION WHERE (NOM_UT LIKE '"+ui->nomut_in->text()+"');");

    QString Nom=model.data(model.index(0, 0)).toString();
    QString mdp=model.data(model.index(0, 1)).toString();
    qInfo() << "Nom "<<mdp<<" "<<Nom;

    //  if ((ui->mdp_in2->text()==mdp) && (Nom!=""))



    if ((mdp==ui->mdp_in->text()) && (Nom!=""))
    {
        bool test=true;
        c.createconnect();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                                     QObject::tr("connection successful.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            e.exec();

        }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                  QObject::tr("connection failed.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else {

        QMessageBox::critical(nullptr, QObject::tr("Password incorrect"),
                              QObject::tr("Please check your password or try again later.\n"
                                          ), QMessageBox::Cancel);

    }

}

void MainWindow::on_oublie_clicked()
{

    Forgot f;
    f.exec();

    /*
    QSqlQueryModel model;

     model.setQuery("SELECT * from INF_CONNEXION WHERE (NOM_UT LIKE '"+ui->nomut_in->text()+"');");

    QString Nom=model.data(model.index(0, 2)).toString();
if (Nom!="")
{


 e.exec();
}
else    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("Contact your administrator.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);*/
}

void MainWindow::on_creercmpt_clicked()
{
    //Connection c;

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("khalil");//inserer nom de l'utilisateur
    db.setPassword("employe");//inserer mot de passe de cet utilisateur
    QSqlQuery query(db);
    QSqlQueryModel model;
    if (db.open())
    {
        if (ui->mdp_in2->text()=="")
            QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave password empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);
        else if  (ui->mdp_in2->text()!=ui->mdp_in3->text())
            QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Passwords don't match.\n""Click Cancel to retry ."), QMessageBox::Cancel);
        else if (ui->nomut_in2->text()=="")
            QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave Username Empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);
        else


        {

            // model.setQuery("insert into INF_CONNEXION(NOM_UT,MDP,ADRESSE_MAIL) values (:NOM_UT, :MDP,:AD);");
            query.prepare("insert into INF_CONNEXION(NOM_UT,MDP,ADRESSE_MAIL)" "values (:NOM_UT, :MDP, :AD);");

            query.bindValue(":NOM_UT",ui->nomut_in2->text());


            query.bindValue(":MDP",ui->mdp_in2->text());
            query.bindValue(":AD",ui->Adresse_in->text());
            if ( query.exec())
                QMessageBox::information(nullptr, QObject::tr("Done"), QObject::tr("Credentials added.\n""Click Cancel to Continue ."), QMessageBox::Cancel);


        }
    }


}

/*
 *
 *
 * void MainWindow::on_creercmpt_clicked()
{
    Connection c;


      QSqlQuery query;
     // qInfo() << "Nom"<<" "<<ui->mdp_in2->text()<<endl;
     if (ui->mdp_in2->text()=="")
         QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave password empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);
     else if  (ui->mdp_in2->text()!=ui->mdp_in3->text())
         QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Passwords don't match.\n""Click Cancel to retry ."), QMessageBox::Cancel);
    else if (ui->nomut_in2->text()=="")
         QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave Username Empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);


else


     {
        c.createconnect();
         query.prepare("insert into INF_CONNEXION(NOM_UT,MDP) values (:NOM_UT, :MDP);");

       query.bindValue(":NOM_UT",ui->nomut_in2->text());

        query.bindValue(":MDP",ui->mdp_in2->text());
     query.exec();




     }





}*/

