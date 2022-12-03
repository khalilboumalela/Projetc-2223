#include "forgot.h"
#include "ui_forgot.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QMessageBox>
#include "connection.h"
#include "smtp.h"
//#include <QtGui/QApplication>
/*#include "SmtpMime"
 * */
//#include <QCoreApplication>


Forgot::Forgot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Forgot)
{
    ui->setupUi(this);
    Connection c;
    c.createconnect();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("khalil");//inserer nom de l'utilisateur
    db.setPassword("employe");//inserer mot de passe de cet utilisateur
    db.open();
}

Forgot::~Forgot()
{
    delete ui;
}

void Forgot::on_Submit_clicked()
{
   /* Connection c;
    c.createconnect();
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("khalil");//inserer nom de l'utilisateur
    db.setPassword("employe");//inserer mot de passe de cet utilisateur
    db.open();*/
    QSqlQuery query;

    QSqlQueryModel model;


     model.setQuery("SELECT * from INF_CONNEXION WHERE (ADRESSE_MAIL LIKE '"+ui->Adresse_mail->text()+"');");
    QString N=model.data(model.index(0, 0)).toString();
    QString Nom=model.data(model.index(0, 2)).toString();
    qInfo() << "Nom"<<" "<<Nom<<endl;
if (ui->Adresse_mail->text()!=ui->Adresse_mail_2->text())
{
    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                    QObject::tr("Mails adresses don't match.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else if ((Nom!="") && (ui->mdp_in->text()!=""))
{

    query.prepare("UPDATE INF_CONNEXION SET MDP= :nom2   where ADRESSE_MAIL= :cin2 ;");
    query.bindValue(":nom2",ui->mdp_in->text() );
    query.bindValue(":cin2",ui->Adresse_mail->text() );

    if (query.exec()) {QMessageBox::information(nullptr, QObject::tr("Done"),
                                            QObject::tr("Password changed.\n"
                                                        "Click OK to Continue."), QMessageBox::Ok);
        //

      qDebug() << QSslSocket::supportsSsl() << QSslSocket::sslLibraryBuildVersionString() << QSslSocket::sslLibraryVersionString();

        Smtp* smtp = new Smtp("mohamedkhalil.boumelala@esprit.tn","Jihenepqt123", "smtp.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        smtp->sendMail("mohamedkhalil.boumelala@esprit.tn", "khalilboumalala@gmail.com", "Votre mot de passe a été modifié","Salut");











        //
 e.exec();}
    else
        QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                               QObject::tr("Contact your administrator.\n"
                                           "Click Cancel to exit."), QMessageBox::Cancel);
}
else    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("Contact your administrator.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);





}
