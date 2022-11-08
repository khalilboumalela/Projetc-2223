#include "emp.h"
#include "ui_emp.h"
#include "employes.h"
#include <QMessageBox>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>

Emp::Emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emp)
{
    ui->setupUi(this);
    ui->l_CIN->setValidator(new QIntValidator(0,999999999,this));
       ui->l_tel->setValidator(new QIntValidator(0,99999999,this));
       ui->l_salaire->setValidator(new QIntValidator(0,999999999,this));
       ui->tab_etud->setModel(e.afficher());


       mCamera =new QCamera(this);
       mCameraViewfinder = new QCameraViewfinder(this);
       mCameraImageCapture = new QCameraImageCapture(mCamera,this);
       m = new QVBoxLayout;
       mOptionsmenu = new QMenu("Ouvrir",this);
       mOuvrir = new QAction("Ouvrir",this);
       mCapturer = new QAction("Capturer",this);
       mSauv = new QAction("Sauvegarder",this);

       mOptionsmenu->addActions({mOuvrir,mCapturer,mSauv});
       ui->Camera->setMenu(mOptionsmenu);
        mCamera->setViewfinder(mCameraViewfinder);
       m->addWidget(mCameraViewfinder);
       m->setMargin(0);
        ui->scrollArea->setLayout(m);
        connect(mOuvrir,&QAction::triggered, [&](){
        mCamera->start();
        });
        connect(mCapturer,&QAction::triggered, [&](){
        mCamera->stop();
        });
        connect(mSauv,&QAction::triggered, [&](){
        auto filename= QFileDialog::getSaveFileName(this,"Capture","/",
                                     "image(*.jpg;*.jpeg)");
        if (filename.isEmpty())
        {return ;}
        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
        QImageEncoderSettings imageEncoderSettings;
        imageEncoderSettings.setCodec("image.jpeg");
        imageEncoderSettings.setResolution(1600, 1200);
        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
        mCamera->setCaptureMode(QCamera::CaptureStillImage);
        mCamera->start();
        mCamera->searchAndLock();
        mCameraImageCapture->capture(filename);
        mCamera->unlock();

        });



}

Emp::~Emp()
{
    delete ui;
}

void Emp::on_ajouter_clicked()
{employes E;
    if (ui->l_CIN->text()!="")
{ui->tab_etud->setModel(e.afficher());
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
    else {

        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                    QObject::tr("Please don't leave Cin empty.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }


}

void Emp::on_supprimer_clicked()
{    if (ui->l_CIN_2->text()!="")
    {
    int cin=ui->l_CIN_2->text().toInt();
    int test=e.supprimer(cin);
    if (test==1)
    {       ui->tab_etud->setModel(e.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                    QObject::tr("Supression effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);}


                    else if (test==2)
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                            QObject::tr("Cin n'existe pas.\n"
                                                        "Click Cancel to exit."), QMessageBox::Cancel);

        else
                        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                                    QObject::tr("Suppression non effectué.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
        else {

            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Please don't leave Cin empty.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

}



void Emp::on_modifier_2_clicked()
{
    if (ui->l_CIN_3->text()!="")
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
        else {

            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Please don't leave Cin empty.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
       

}



void Emp::on_modifier_clicked()
{
    if (ui->l_CIN_3->text()!="")
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
        else {

            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                        QObject::tr("Please don't leave Cin empty.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

}

void Emp::on_Tri_cin_clicked()
{
    QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();


                   model->setQuery("select * from EMPLOYE order by CIN ");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom "));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN "));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire  "));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction "));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
                   model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));
                            ui->tab_etud->setModel(model);
                            ui->tab_etud->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();

}

void Emp::on_Tri_nom_clicked()
{
    QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();


                   model->setQuery("select * from EMPLOYE order by NOM");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom "));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN "));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire  "));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction "));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
                   model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));
                            ui->tab_etud->setModel(model);
                            ui->tab_etud->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();
}

void Emp::on_Tri_fonct_clicked()
{
    QMessageBox msgBox ;
                QSqlQueryModel * model= new QSqlQueryModel();


                   model->setQuery("select * from EMPLOYE order by FONCTION");
                   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
                   model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom "));
                   model->setHeaderData(2, Qt::Horizontal, QObject::tr("CIN "));
                   model->setHeaderData(3, Qt::Horizontal, QObject::tr("salaire  "));
                   model->setHeaderData(4, Qt::Horizontal, QObject::tr("fonction "));
                   model->setHeaderData(5, Qt::Horizontal, QObject::tr("TEL"));
                   model->setHeaderData(6, Qt::Horizontal, QObject::tr("sexe"));
                            ui->tab_etud->setModel(model);
                            ui->tab_etud->show();
                            msgBox.setText("Tri avec succés.");
                            msgBox.exec();
}

void Emp::on_Recherche_clicked()
{
    employes E;

   ui->tab_etud->setModel( E.rechercher(ui->l_r_2->text()));

}
