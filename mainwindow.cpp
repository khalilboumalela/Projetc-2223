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

    ////arduino
    int ret=A.connect_arduino(); // lancer la connexion à arduino
          switch(ret){
          case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
              break;
          case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
             break;
          case(-1):qDebug() << "arduino is not available";
          }
           QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));

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

    model.setQuery("SELECT * from INF_CONNEXION WHERE (NOM_UT  LIKE '"+ui->nomut_in->text()+"');");

    QString Nom=model.data(model.index(0, 0)).toString();
    QString mdp=model.data(model.index(0, 1)).toString();
    QString rfid=model.data(model.index(0, 3)).toString();


    //  if ((ui->mdp_in2->text()==mdp) && (Nom!=""))


/*QString at=A.read_from_arduino();

if (at=="") at = ui->RFID->text();*/
qInfo() << "RFID= "<<rfid<<" "<<Nom;
//A.write_to_arduino(Nom);
    if ((mdp==ui->mdp_in->text()) && (Nom!=""))// && (rfid==ui->RFID->text()))
    {/*at=Nom;
       A.write_to_arduino2("+");
       A.write_to_arduino(at);*/
        bool test=true;
        c.createconnect();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                                     QObject::tr("connection successful.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);

            this->hide();
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
       // ui->mdp_2->setText("Please Scan RFID Card");


    }

}

void MainWindow::on_oublie_clicked()
{

    Forgot f;
    f.exec();

}

void MainWindow::on_creercmpt_clicked()
{
  // Connection c;
    //c.createconnect();

    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("khalil");//inserer nom de l'utilisateur
    db.setPassword("employe");//inserer mot de passe de cet utilisateur

    QSqlQuery query(db);
    //QSqlQueryModel model;
    QString at="";
    if (db.open())
    {
        if (ui->mdp_in2->text()=="")
        {QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave password empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);

        }else if  (ui->mdp_in2->text()!=ui->mdp_in3->text())
         {   QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Passwords don't match.\n""Click Cancel to retry ."), QMessageBox::Cancel);
        }else if (ui->nomut_in2->text()=="")
         {   QMessageBox::critical(nullptr, QObject::tr("ERROR"), QObject::tr("Don't leave Username Empty.\n""Click Cancel to retry ."), QMessageBox::Cancel);
   }else


        {//at=A.read_from_arduino();

            // model.setQuery("insert into INF_CONNEXION(NOM_UT,MDP,ADRESSE_MAIL) values (:NOM_UT, :MDP,:AD);");
            query.prepare("insert into INF_CONNEXION(NOM_UT,MDP,ADRESSE_MAIL,RFID)" "values (:NOM_UT, :MDP, :AD,:RFID);");

            query.bindValue(":NOM_UT",ui->nomut_in2->text());
            query.bindValue(":MDP",ui->mdp_in2->text());
            query.bindValue(":AD",ui->Adresse_in->text());
            /*if (at!="") query.bindValue(":RFID",at); else
                 query.bindValue(":RFID",ui->RFID2->text());*/
qInfo() << "RFID= "<<at<<" "<<endl;
             //if (at!="") ui->mdp_3->setText("RFID Scanned!");
             //else ui->mdp_3->setText("Please Scan RFID Card");
        if (query.exec())
                {qInfo() << "RFID2= "<<at<<" "<<endl;
                QMessageBox::information(nullptr, QObject::tr("Done"), QObject::tr("Credentials added.\n""Click Cancel to Continue ."), QMessageBox::Cancel);
}
        }
    }//qInfo() << "RFID4= "<<at<<" "<<endl;
}



void MainWindow::on_Scan_clicked()
{/*
    QString at=A.read_from_arduino();

    at=at.simplified();
    at.replace(" ","");

    if (at!="") ui->RFID->setText(at);*/
}


void MainWindow::on_seconnecter_3_clicked()
{/*
    QString at=A.read_from_arduino();
 at=at.simplified();
 at.replace(" ","");
    if (at!="") ui->RFID2->setText(at);*/
}


//***************** Gestion Equipements********************


