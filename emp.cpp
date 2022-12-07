#include "emp.h"
#include "ui_emp.h"
#include "connection.h"
#include "employes.h"
#include <QMessageBox>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QTextDocument>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include<QPainter>
#include <QSettings>
#include<QDateTime>
#include<QTimer>

//******Equipements********
#include "dialog_map.h"
#include "dialog_stats.h"
#include <QIntValidator>
#include <QDesktopServices>
#include <QPushButton>
#include <QDebug>

#include "exportexcelobject.h"
#include "equipement.h"

#include "dialog_map.h"
#include "dialog_stats.h"

//
//********Reclamations****//
#include <QString>
#include <QMediaPlayer>
#include <QFile>
#include <QVideoWidget>
#include "smtp.h"
#include "reclamation.h"
#include "connection.h"
#include <QSqlQueryModel>
#include <QLabel>
#include<QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include "arduino.h"
/*#include "Emp.h"
#include "ui_Emp.h"*/


#include <QtGui/QIntValidator>
#include<QIntValidator>
#include<QMessageBox>
#include<QDesktopServices>
#include<QFileDialog>
#include <QPushButton>


#include<QSqlQuery>

#include<QDoubleValidator>
#include<QtDebug>
#include<QObject>
//#include <Q>
#include <QDateTime>
#include <QFile>
#include <QMessageBox>

#include <QTextDocument>
#include <QFileDialog>
#include <QDate>
#include <QTableWidgetItem>
#include <QTabWidget>
#include <QPixmap>
#include "QtPrintSupport"
#include <QTimer>
#include <QPieSlice>
#include <QPieSeries>
#include <QtCharts>






//****Sponsors****
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QPainter>
#include <QTextStream>
#include <QFileDialog>
#include <QTextDocument>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <strstream>
#include <QSystemTrayIcon>
#include <QRegExpValidator>
#include <QDesktopServices>
#include <QUrl>
#include <QPdfWriter>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QSqlQuery>

#include "sponsor.h"
#include "qrcode.h"
#include<QPixmap>
#include<QListWidget>



#include <QtWidgets>
//****Emiss***

#include "emission.h"
#include <QMessageBox>
#include <QDebug>
#include <QDialog>
#include <QtSql/QSqlQuery>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QSortFilterProxyModel>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include<QWidget>
#include<QtSvg/QSvgRenderer>
#include<QDirModel>
#include"qrcode.h"
#include<fstream>
#include "connection.h"
#include "smtp.h"
#include <QStringList>
#include <QFileInfo>
#include "mainwindow.h"
#include <QPrintDialog>
#include "exportexcelobject.h"
#include"todolist.h"



using qrcodegen::QrCode;
using qrcodegen::QrSegment;


//
Emp::Emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emp)
{
    ui->setupUi(this);
    //**************** Employes*************
    ui->l_CIN->setValidator(new QIntValidator(0,999999999,this));
       ui->l_tel->setValidator(new QIntValidator(0,99999999,this));
       ui->l_salaire->setValidator(new QIntValidator(0,999999999,this));
       ui->tab_etud->setModel(e.afficher());

       /////////maps

       QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::organizationName(), QCoreApplication::applicationName());

       ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

/////////// arduino
 int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
        QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
        //le slot update_label suite à la reception du signal readyRead (reception des données).


   //horloge
    /*   Timer= new QTimer(this);
       connect (Timer,SIGNAL(timeout()),this,SLOT(son()));
   Timer->start(1000);*/


   QTime time =QTime::currentTime();
   QString time_text =time.toString("hh : mm : ss");
   ui->TIMER->setText("TIMER: "+time_text);

       //////////
///////////camera
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
                                     "(*.Jpg;*.Jpeg)");
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
///////////// fin camera
        });
//

//*************Gestion Equipements***********
  ui->lineEdit_Reff_2->setValidator( new QIntValidator(0, 99999999, this));
    ui->comboBox->setModel(E.afficher_reff());
    ui->tab_Equipement->setModel (E.afficher());
    Connection c;
        bool test=c.CreateConnexion();
        if(test)
        {
            ui->labe_db->setText("Database: CONNECTED");
        }
        else
            ui->labe_db->setText("Database: FAILED");

//***********Reclamations*********
        ui->le_id->setValidator(new QIntValidator (0,9999999, this));
           // ui->tab_employe->setModel(RE.afficher());
        //
            //****Sponsors**
            // ui->tab_sponsor_2->setModel(S.afficher());
            //
        //**Emiss**
        connect(ui->sendMail, SIGNAL(clicked()),this, SLOT(sendMail()));
               connect(ui->browseBtn_7, SIGNAL(clicked()), this, SLOT(browse()));
        //
}

Emp::~Emp()
{
    delete ui;
}

void Emp::on_ajouter_clicked()
{employes E;
    ui->tab_etud->setModel(e.afficher());
    if (ui->l_CIN->text()!="")
{
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


                   model->setQuery("select * from EMPLOYE order by CIN, TEL");
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

void Emp::on_l_r_2_cursorPositionChanged(int arg1, int arg2)
{
    employes E;
    ui->tab_etud->setModel( E.rechercher(ui->l_r_2->text()));

}

void Emp::on_tabWidget_currentChanged(int index)
{
     ui->tab_etud->setModel(e.afficher());
}

void Emp::on_PDF_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tab_etud->model()->rowCount();
                    const int columnCount =ui->tab_etud->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Employes</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_etud->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_etud->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tab_etud->isColumnHidden(column)) {
                                       QString data = ui->tab_etud->model()->data(ui->tab_etud->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);


//            QTextDocument document;
  //          document.setHtml(html);
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("mypdffile.pdf");
            document->print(&printer);
}


void Emp::on_Imprimer_clicked()
{
    QPdfWriter pdf("C:/Users/khali/Downloads/Integrations c++/SmartR/liste.pdf");
                             QPainter painter(&pdf);

                            int i = 4000;
                                 painter.setPen(Qt::red);
                                 painter.setFont(QFont("Arial", 30));
                                 painter.drawText(1100,1200,"Liste Des EMPLOYE");
                                 painter.setPen(Qt::black);
                                 painter.setFont(QFont("Arial", 15));
                                // painter.drawText(1100,2000,afficheDC);
                                 painter.drawRect(100,100,7300,2600);

                                 painter.drawRect(0,3000,9600,500);
                                 painter.setFont(QFont("Arial", 9));
                                 painter.drawText(200,3300,"NOM");
                                 painter.drawText(1300,3300,"PRENOM");
                                 painter.drawText(2100,3300,"CIN");
                                 painter.drawText(3100,3300,"SALAIRE");
                                 painter.drawText(4100,3300,"FONCTION");
                                 painter.drawText(5100,3300,"TEL");
                                 painter.drawText(6100,3300,"SEXE");

                                 QSqlQuery query;
                                 query.prepare("select * from EMPLOYE");
                                 query.exec();
                                 while (query.next())
                                 {
                                     painter.drawText(200,i,query.value(0).toString());
                                     painter.drawText(1300,i,query.value(1).toString());
                                     painter.drawText(2100,i,query.value(2).toString());
                                     painter.drawText(3100,i,query.value(3).toString());
                                     painter.drawText(4100,i,query.value(4).toString());
                                     painter.drawText(5100,i,query.value(5).toString());
                                     painter.drawText(6100,i,query.value(6).toString());




                                    i = i + 500;
                                 }


              int reponse = QMessageBox::Yes;
                  if (reponse == QMessageBox::Yes)
                  {
                      QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;

                      notifyIcon->show();
                     notifyIcon->setIcon(QIcon(":/icon.png"));

                      notifyIcon->showMessage("GESTION DES  EMPLYOES ","Liste employée pret dans PDF",QSystemTrayIcon::Information,15000);

                      painter.end();
                  }
                  if (reponse == QMessageBox::No)
                  {
                       painter.end();
                  }
}


void Emp::on_Emp_2_currentChanged(int index)
{
     ui->tab_etud->setModel(e.afficher());
}



//*********Equipements**

void Emp::update_label()
{


while((A.getdata().size()<5))
{

data=A.read_from_arduino();
break;

}


if(data!="")
{
if(data=="feu"){
  A.burn();
 qDebug() << "burned" ;
     ui->tab_Equipement->setModel (E.afficher());
}


}





data="";
}
/*
Emp::~Emp()
{
    delete ui;
}
*/

void Emp::on_pB_AjouterP_clicked()
{
    int REFFERANCE=ui->lineEdit_Reff_2->text().toInt();
    QString NOM=ui->lineEdit_Nom_2->text();
    int QUANTITE=ui->LineEdit_Quantite_2->text().toInt();
    int PRIX=ui->lineEdit_Prix_2->text().toInt();
    QDate DATE_A=ui->dateEdit_DateA_2->date();
    equipement E(REFFERANCE,NOM,QUANTITE,PRIX,DATE_A);
    bool test=E.ajouter();
    if(test)
    {
        ui->label_Info->setText("Ajout effectué");
        ui->comboBox->setModel(E.afficher_reff());
        ui->tab_Equipement->setModel(E.afficher());
    }
    else
    {
        ui->label_Info->setText("Ajout non effectué");
    }
}

void Emp::on_pB_ModifierP_clicked()
{
    int REFFERANCE=ui->lineEdit_Reff_2->text().toInt();
    QString NOM=ui->lineEdit_Nom_2->text();
    int QUANTITE=ui->LineEdit_Quantite_2->text().toInt();
    int PRIX=ui->lineEdit_Prix_2->text().toInt();
    QDate DATE_A=ui->dateEdit_DateA_2->date();
    equipement E(REFFERANCE,NOM,QUANTITE,PRIX,DATE_A);
    bool test=E.modifier();
    if(test)
    {
        ui->label_Info->setText("Modification effectué");
        ui->tab_Equipement->setModel(E.afficher());
        ui->comboBox->setModel(E.afficher_reff());
    }
    else
    {
        ui->label_Info->setText("Modification non effectué");
    }
}

void Emp::on_pB_SupprimerP_clicked()
{
    equipement E;
    E.setreff(ui->comboBox->currentText().toInt());
    bool test=E.supprimer(E.getreff());
    if(test)
    {
        ui->label_Info->setText("Suppression effectué");
        ui->tab_Equipement->setModel(E.afficher());
        ui->comboBox->setModel(E.afficher_reff());
    }
    else
    {
        ui->label_Info->setText("Suppression non effectué");
    }
}

void Emp::on_pB_TirerParReff_clicked()
{
    ui->label_Info->setText("Tri par Refferance effectué");
    ui->tab_Equipement->setModel(E.tri_reff());
}

void Emp::on_pB_TireParNom_clicked()
{
    ui->label_Info->setText("Tri par Nom effectué");
    ui->tab_Equipement->setModel(E.tri_nom());
}

void Emp::on_pB_TirerParQuantite_clicked()
{
    ui->label_Info->setText("Tri par Quantite effectué");
    ui->tab_Equipement->setModel(E.tri_quant());
}

void Emp::on_pB_Recherche_clicked()
{
    equipement E;
    QString text;

    if (ui->rB_reff->isChecked()==true)
    {
        E.clearTable(ui->tab_Equipement);
            int REFFERANCE=ui->lineEdit_Recherche->text().toInt();
            E.chercheReff(ui->tab_Equipement,REFFERANCE);
    }
    if (ui->rb_Nom->isChecked()==true)
    {
        E.clearTable(ui->tab_Equipement);
            QString NOM=ui->lineEdit_Recherche->text();
            E.chercheNom(ui->tab_Equipement,NOM);
    }
}

void Emp::on_comboBox_currentIndexChanged(int)
{
    int reff=ui->comboBox->currentText().toInt();
    QString reff_1=QString::number(reff);
    QSqlQuery query;
    query.prepare("SELECT * FROM EQUIPEMENT where REFFERANCE='"+reff_1+"'");
    if(query.exec())
    {
        while (query.next())
        {
            ui->lineEdit_Reff_2->setText(query.value(0).toString()) ;
            ui->lineEdit_Nom_2->setText(query.value(1).toString()) ;
            ui->LineEdit_Quantite_2->setText(query.value(2).toString()) ;
            ui->lineEdit_Prix_2->setText(query.value(3).toString()) ;
            ui->dateEdit_DateA_2->setDate(query.value(4).toDate()) ;
        }
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK "),
                              QObject::tr("ECHEC DE chargement .\n""Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void Emp::on_pB_export_pdf_clicked()
{
    QPdfWriter pdf("C:/Users/MSI/Desktop/GestionEquipement/Liste.pdf");
    QPainter painter(&pdf);
    int i = 4000;
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30));
    painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/alamo/Desktop/Gestion d'equipement/Logo.png"));
    painter.drawText(3000,1500,"LISTE DES EQUIPEMENT");
    painter.setPen(Qt::blue);
    painter.setFont(QFont("Arial", 50));
    painter.drawRect(2700,200,6300,2600);
    painter.drawRect(0,3000,9600,500);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 9));
    painter.drawText(300,3300,"REFFERANCE");
    painter.drawText(2300,3300,"NOM");
    painter.drawText(4300,3300,"QUANTITE");
    painter.drawText(6300,3300,"PRIX");
    painter.drawText(8000,3300,"DATE_A");
    QSqlQuery query;
    query.prepare("<SELECT CAST( GETDATE() AS Date ) ");
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti=localtime(&tt);
    asctime(ti);
    painter.drawText(500,300, asctime(ti));
    query.prepare("select * from EQUIPEMENT");
    query.exec();
    while (query.next())
    {
        painter.drawText(300,i,query.value(0).toString());
        painter.drawText(2300,i,query.value(1).toString());
        painter.drawText(4300,i,query.value(2).toString());
        painter.drawText(6300,i,query.value(3).toString());
        painter.drawText(8000,i,query.value(4).toString());
        painter.drawText(10000,i,query.value(5).toString());
        i = i +500;
    }
    int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
    if (reponse == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/MSI/Desktop/GestionEquipement/Liste.pdf"));
        painter.end();
    }
    if (reponse == QMessageBox::No)
    {
        painter.end();
    }
}

void Emp::on_pB_Stats_clicked()
{
    Dialog_Stats stats;
    stats.setModal(true);
    stats.exec();
}

void Emp::on_pB_Map_clicked()
{

    Dialog_map map;
    map.setModal(true);
    map.exec();
}
void Emp::on_pushButton_Fermer_clicked()
{
 close();
}

void Emp::on_pB_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "BILLETS", ui->tab_Equipement);

        //colums to export
        obj.addField(0, "REFFERANCE", "char(20)");
        obj.addField(1, "NOM", "char(20)");
        obj.addField(2, "QUANTITE", "char(20)");
        obj.addField(3, "PRIX", "char(20)");
        obj.addField(4, "DATE_A", "char(20)");



        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}

//**********Gestion Reclamations*****



void Emp::on_pb_ajouter_clicked()
{
ui->tab_employe->setModel(RE.afficher());
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int numero=ui->le_numero->text().toInt();
    QString adresse=ui->le_adresse->text();

    reclamation RE(id,nom,prenom,numero,adresse);
    bool test=RE.ajouter();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("Ajout avec success");
    ui->tab_employe->setModel(RE.afficher());}
    else
        msgBox.setText("Echec d'ajout");
    msgBox.exec();

}

void Emp::update_label2()
{
 //   data=A.read_from_arduino();

    if(data=="1")

        ui->engine_state->setText("ON"); // si les donnÃ©es reÃ§ues de arduino via la liaison sÃ©rie sont Ã©gales Ã  1
    // alors afficher On

    else if (data=="0")

        ui->label_3->setText("OFF");   // si les donnÃ©es reÃ§ues de arduino via la liaison sÃ©rie sont Ã©gales Ã  0
     //alors afficher Off
}


void Emp::on_pb_supprimer_clicked()
{
reclamation E1; E1.setid(ui->le_id_supp->text().toInt());
bool test=E1.supprimer(E1.getid());
QMessageBox msgBox;
if(test)
   { msgBox.setText("Suppression avec success");
   ui->tab_employe->setModel(RE.afficher());
}
else
    msgBox.setText("Echec de suppression");

msgBox.exec();
}



void Emp::on_pb_play_vid_clicked()
{
    player= new QMediaPlayer;
    vw=new QVideoWidget;

    auto filename=QFileDialog::getOpenFileName(this,"import mp4 file",QDir::rootPath(),"Excel Files(*.mp4)");


    player->setVideoOutput(vw);
    player->setMedia(QUrl::fromLocalFile(filename));
    vw->setGeometry(100,100,300,400);
    vw->show();
    player->play();
}

void Emp::on_pb_stop_vid_clicked()
{
    player->stop();
    vw->close();

}
  //mailing
void  Emp::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );


}






void Emp::on_pb_modifier_clicked()
{ui->tab_employe->setModel(RE.afficher());
    int id=ui->le_id->text().toInt();
    QString nom=ui->le_nom->text();
    QString prenom=ui->le_prenom->text();
    int numero=ui->le_numero->text().toInt();
    QString adresse=ui->le_adresse->text();

    reclamation E(id,nom,prenom,numero,adresse);
    bool test=RE.modifier();
    QMessageBox msgBox;
    if(test)
    {
        msgBox.setText("modification avec success");
    ui->tab_employe->setModel(RE.afficher());}
    else
        msgBox.setText("Echec de modification");
    msgBox.exec();

}









/*
void Emp::on_pb_on_clicked()
{
reclamation.connect_arduino();
read_from_arduino();



}

void Emp::on_pb_off_clicked()
{
    close_arduino();
}
*/
void Emp::on_button_trier_clicked()
{
  reclamation p;
             ui->tab_employe->setModel(p.tri_id());
            QMessageBox::information(nullptr, QObject::tr("Ok"),
                 QObject::tr("tri effectué.\n"
                             "Click Cancel to exit."), QMessageBox::Cancel);
                ui->tab_employe->setModel(p.tri_id());

}

void Emp::on_pdf_clicked()
{
    QSqlDatabase db;

                    QTableView tableView;
                    QSqlQueryModel * Modal=new  QSqlQueryModel();

                    QSqlQuery qry;
                     qry.prepare("SELECT* FROM RECLAMATION");
                     qry.exec();
                     Modal->setQuery(qry);
                     tableView.setModel(Modal);

                     db.close();

                     QString strStream;
                     QTextStream out(&strStream);

                     const int rowCount = tableView.model()->rowCount();
                     const int columnCount =  tableView.model()->columnCount();

                     const QString strTitle ="ListeDesRECLAMATIONS";

                     out <<  "<html>\n"
                             "<img src='C:/Users/ASUS/Desktop/Smart Parc/SmartParc.png' height='155' width='140'/>"
                         "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                         <<  QString("<title>%1</title>\n").arg(strTitle)
                         <<  "</head>\n"
                         "<body bgcolor=#ffffff link=#5000A0>\n"
                        << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("LISTE DES clients")
                        <<"<br>"

                        <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                     out << "<thead><tr bgcolor=#f0f0f0>";
                     for (int column = 0; column < columnCount; column++)
                         if (!tableView.isColumnHidden(column))
                             out << QString("<th>%1</th>").arg(tableView.model()->headerData(column, Qt::Horizontal).toString());
                     out << "</tr></thead>\n";

                     for (int row = 0; row < rowCount; row++)
                     {
                         out << "<tr>";
                         for (int column = 0; column < columnCount; column++)
                         {
                             if (!tableView.isColumnHidden(column))
                             {
                                 QString data = tableView.model()->data(tableView.model()->index(row, column)).toString().simplified();
                                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                             }
                         }
                         out << "</tr>\n";
                     }
                     out <<  "</table>\n"
                             "<br><br>"
                             <<"<br>"
                             <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                         out << "<thead><tr bgcolor=#f0f0f0>";

                             out <<  "</table>\n"

                         "</body>\n"
                         "</html>\n";

                     QTextDocument *reclamation= new QTextDocument();
                    reclamation->setHtml(strStream);

                     QPrinter printer;
                     QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                     if (dialog->exec() == QDialog::Accepted)
                     {

                         reclamation->print(&printer);
                     }
                     printer.setOutputFormat(QPrinter::PdfFormat);
                     printer.setPaperSize(QPrinter::A4);
                     printer.setOutputFileName("/tmp/reclamation.pdf");
                     printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                     delete reclamation;
}

void Emp::on_image_clicked()
{
    QString filename= QFileDialog::getOpenFileName(this,tr("CHOOSE"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *.gif)"));
        if(QString::compare(filename,QString())!=0)
        {
            QImage image;
            bool valid = image.load(filename);
            if(valid)
            {
                image= image.scaledToWidth(ui->IMG_Added->width(), Qt::SmoothTransformation);
                image= image.scaledToHeight(ui->IMG_Added->height(), Qt::SmoothTransformation);
                ui->IMG_Added->setPixmap(QPixmap::fromImage(image));
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("Add Failed !"), QMessageBox::Ok);
            }
        }
}

void Emp::on_radioButton_clicked()
{
   reclamation c;
        QSqlQueryModel* model=new QSqlQueryModel();
    c.geo();


}

void Emp::on_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select * from RECLAMATION where NUMERO>= 200");
            float dispo1=model->rowCount();

            model->setQuery("select * from RECLAMATION where NUMERO <200");
            float dispo=model->rowCount();

            float total=dispo1+dispo;
                QString a=QString(" urgent. " +QString::number((dispo1*100)/total,'f',2)+"%" );
                QString b=QString(" normales.  "+QString::number((dispo*100)/total,'f',2)+"%" );
                QPieSeries *series = new QPieSeries();
                series->append(a,dispo1);
                series->append(b,dispo);
            if (dispo1!=0)
            {QPieSlice *slice = series->slices().at(0);
                slice->setLabelVisible();
                slice->setPen(QPen());}
            if ( dispo!=0)
            {
                QPieSlice *slice1 = series->slices().at(1);
                slice1->setLabelVisible();
            }

            QChart *chart = new QChart();

            chart->addSeries(series);
            chart->setTitle("nombres de reclamations "+ QString::number(total));
            chart->legend()->hide();

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            chartView->resize(1000,500);
            chartView->show();
}




void Emp::on_recherche_textChanged()
{
    reclamation a;
    QString rech= ui ->recherche->text();
    ui ->tab_employe ->setModel(a.recherche(rech));
}
//
//**********Sponsors******


void Emp::on_pb_ajouter_2_clicked()
{ui->tab_sponsor_2->setModel(S.afficher());
    QString nom=ui->le_nom_2->text();
    QString localisation=ui->le_localisation_2->text();
    int numtel=ui->le_num_2->text().toInt();
    int code=ui->le_code_2->text().toInt();
    QString email=ui->le_ad_2->text();



   Sponsor E(nom,localisation,numtel,code,email);

bool test=E.ajouter();

if(test)
{

    QMessageBox::information(nullptr, QObject::tr("ok"),
                QObject::tr("Ajouter effectué.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
    ui->tab_sponsor_2->setModel(Etmp.afficher());
}
else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                QObject::tr("Ajouter non  effectué.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);

}



void Emp::on_pb_supprimer_2_clicked()
{


    int code =ui->le_code_supp_2->text().toInt();
    bool test=Etmp.supprimer(code);
    if(test)
    {
       QMessageBox::information(nullptr,QObject::tr("ok"),
                                QObject::tr("suppression effectuee \n"
                                            "click Cancel to exit."), QMessageBox::Cancel);
       ui->tab_sponsor_2->setModel(Etmp.afficher());
    }
    else
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                               QObject::tr("suppression non effectuee.\n"
                                      "click Cancel to exit."),QMessageBox::Cancel);

}




void Emp::on_pb_modifier_2_clicked()
{
    Sponsor E1;
     int code =ui->le_code_supp_2->text().toInt();
bool test=Etmp.supprimer(code);
    if(!test){
        QMessageBox::critical(nullptr, QObject::tr("nope"),
                    QObject::tr("update failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);



    }
    else
    {

        QString nom=ui->le_nom_2->text();
        QString localisation=ui->le_localisation_2->text();
        int numtel=ui->le_num_2->text().toInt();
        int code=ui->le_code_2->text().toInt();
        QString email=ui->le_ad_2->text();



       Sponsor E(nom,localisation,numtel,code,email);

      bool test1=E.ajouter();
   if(test1)
{

            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("update successful.\n"
                                    "update effectuer."), QMessageBox::Cancel);
            ui->tab_sponsor_2->setModel(E.afficher());


}
        else

            QMessageBox::critical(nullptr, QObject::tr("nope"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}



void Emp::on_pushButton_9_clicked()
{
    Sponsor E1;
    E1.setcode(ui->le_code_2->text().toInt());
    bool test=E1.recherche(E1.getcode());
 ui->tab_sponsor_3->setModel(E1.afficher1());
    if(test){


        QMessageBox::information(nullptr, QObject::tr("ok"),
                    QObject::tr("numero found.\n"
                                "rechercher effectuer."), QMessageBox::Cancel);


    }
    else
           QMessageBox::critical(nullptr, QObject::tr("nope"),
                       QObject::tr("numero not found .\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

}
QString imgx="";
/*
void Emp::on_pdf_clicked()
{


        QPdfWriter pdf("C:/Users/wildb/OneDrive/Desktop/projet qt/sponsor/sponsor.pdf");

           QPainter painter(&pdf);
           int i = 4000;
                  painter.setPen(Qt::darkCyan);
                  painter.setFont(QFont("Time New Roman", 25));
                  painter.drawText(3000,1400,"SPONSOR");
                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3000,9400,500);
                  painter.setFont(QFont("Time New Roman", 9));
                  painter.drawText(400,3300,"NOM");
                  painter.drawText(1350,3300,"LOCALISATION");
                  painter.drawText(2200,3300,"NUMTEL");
                  painter.drawText(3400,3300,"CODE");
                  painter.drawText(4400,3300," EMAIL");

                  painter.drawRect(100,3000,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from Sponsor");
                  query.exec();
                  while (query.next())
                  {

                      painter.drawText(1350,i,query.value(1).toString());
                      painter.drawText(2300,i,query.value(2).toString());
                      painter.drawText(3400,i,query.value(3).toString());
                      painter.drawText(4400,i,query.value(4).toString());
                      painter.drawText(6200,i,query.value(5).toString());




                     i = i + 350;
                  }
                  QMessageBox::information(this, QObject::tr("PDF Saved Successfuly!"),
                  QObject::tr("PDF Saved Successfuly!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }




*/



void Emp::on_pushButton_2_clicked()

{
    Sponsor E;
    QMessageBox::information(nullptr, QObject::tr("Ok"),
             QObject::tr("tri effectué.\n"
                         "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_sponsor_5->setModel(E.tri_code());
}









/*void Emp::on_pushButtonqrcode_clicked()
{




   //QString code=ui->CINQR->text();
    QSqlQuery qry;
    qry.prepare("select * from Sponsor where id = :id; ");
   //qry.bindValue(":id",code);
    qry.exec();


     QString nom,prenom,ad_mail,num_tlf,adresse;//attributs
     QString idc;


   while(qry.next()){

        idc=qry.value(0).toString();
        nom=qry.value(1).toString();
        prenom=qry.value(2).toString();
        ad_mail=qry.value(3).toString();
        num_tlf=qry.value(4).toString();
        adresse=qry.value(5).toString();




    }
    idc=QString(idc);



          // nom="nom:\t" +idc+ " localisation:\t" +localisation+ " numtel:\t" +numtel+" code:\t" +code+ " email:\t" +email ;
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(idc.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);

    // Read the black & white pixels
    QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
    for (int y = 0; y < qr.getSize(); y++) {
        for (int x = 0; x < qr.getSize(); x++) {
            int color = qr.getModule(x, y);  // 0 for white, 1 for black

            // You need to modify this part
            if(color==0)
                im.setPixel(x, y,qRgb(254, 254, 254));
            else
                im.setPixel(x, y,qRgb(0, 0, 0));
        }
    }
    im=im.scaled(200,200);
              //ui->qrcodeLabel->setPixmap(QPixmap::fromImage(im));

}*/


void Emp::on_pushButton_12_clicked()
{


        QPdfWriter pdf("C:/Users/wildb/OneDrive/Desktop/projet qt/his/his.pdf");

           QPainter painter(&pdf);
           int i = 4000;
                  painter.setPen(Qt::darkCyan);
                  painter.setFont(QFont("Time New Roman", 25));
                  painter.drawText(3000,1400,"HISTORIQUE");
                  painter.setPen(Qt::black);
                  painter.setFont(QFont("Time New Roman", 15));
                  painter.drawRect(100,100,9400,2500);
                  painter.drawRect(100,3000,9400,500);
                  painter.setFont(QFont("Time New Roman", 9));
                  painter.drawText(400,3300,"NOM");


                  painter.drawRect(100,3000,9400,9000);

                  QSqlQuery query;
                  query.prepare("select * from Sponsor");
                  query.exec();
                  while (query.next())
                  {

                      painter.drawText(1350,i,query.value(1).toString());




                     i = i + 350;
                  }
                  QMessageBox::information(this, QObject::tr("PDF Saved Successfuly!"),
                  QObject::tr("PDF Saved Successfuly!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
    }

void Emp::on_on_btn_2_image_clicked()

{

  /*   //  int tabeq=ui->tableView_2->currentIndex().row();

        /*QVariant id=ui->tableView_2->model()->data(ui->tableView_2->model()->index(0,0)); lghalta hne asmaani khela
        qInfo() << "aa "<<endl;
        QString idc=id.toString();
       QString code=ui->CINQR->text();
        QSqlQuery qry;
        qry.prepare("select * from Sponsor where id = :code; ");
       qry.bindValue(":id",code);
        qry.exec();


         QString nom,prenom,ad_mail,num_tlf,adresse;//attributs
         QString idc;


       while(qry.next()){

            idc=qry.value(0).toString();
            nom=qry.value(1).toString();
            prenom=qry.value(2).toString();
            ad_mail=qry.value(3).toString();
            num_tlf=qry.value(4).toString();
            adresse=qry.value(5).toString();




        }
        idc=QString(idc);

       //QString text = idc ;
               idc="id:\t" +idc+ " Nom:\t" +nom+ " Prenom:\t" +prenom+" ad_mail:\t" +ad_mail+ " num_tlf:\t" +num_tlf ;
        qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(idc.toUtf8().constData(), qrcodegen::QrCode::Ecc::HIGH);

        // Read the black & white pixels
        QImage im(qr.getSize(),qr.getSize(), QImage::Format_RGB888);
        for (int y = 0; y < qr.getSize(); y++) {
            for (int x = 0; x < qr.getSize(); x++) {
                int color = qr.getModule(x, y);  // 0 for white, 1 for black

                // You need to modify this part
                if(color==0)
                    im.setPixel(x, y,qRgb(254, 254, 254));
                else
                    im.setPixel(x, y,qRgb(0, 0, 0));
            }
        }
        im=im.scaled(200,200);
                  ui->qrcodeLabel->setPixmap(QPixmap::fromImage(im));*/


    QString imageFile = QFileDialog::getOpenFileName(this,tr("choose"),"",tr(" (*.png *.jpg *.jpeg)"));//   les img png

         QFileInfo info(imageFile);
         QFileInfo  filename = info.fileName(); //path

         QPixmap image (imageFile);
         ui->lbl_image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );// taille
         image = image.scaled(300,300,Qt::IgnoreAspectRatio,Qt::FastTransformation);
         ui->lbl_image->setPixmap(image);
         ui->lbl_image->show(); // place of png
        // qDebug() << image <<endl << imageFile <<endl<<info.fileName();

        imgx = imageFile;


    }

//****Emiss***
void Emp::on_show_emission_activated(const QModelIndex &index)
{
    QString val=ui->show_emission->model()->data(index).toString();
       QSqlQuery qry ;
          qry.prepare("SELECT * from EMISSION  where ID='"+val+"' ");
          if(qry.exec())
          {
              while(qry.next())
              {


                  ui->li_id->setText(qry.value(0).toString());
                  ui->li_nom->setText(qry.value(1).toString());
                  ui->li_dated->setText(qry.value(2).toString());
                  ui->li_datef->setText(qry.value(3).toString());

              }
          }
          ui->li_id->setText(ui->show_emission->model()->data(ui->show_emission->model()->index(index.row(),0)).toString());
}







void Emp::on_tri_date_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_dated());
}

void Emp::on_tri_datef_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_datef());
}






void Emp::on_pdf_2_clicked()
{
    QString strStream;
                QTextStream out(&strStream);
                                const int rowCount = ui->show_emission->model()->rowCount();
                                const int columnCount = ui->show_emission->model()->columnCount();
                                QString TT = QDate::currentDate().toString("yyyy/MM/dd");



                                out <<  "<html>\n"
                                    "<head>\n"
                                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                                    <<  QString("<title>%1</title>\n").arg("strTitle")
                                    <<  "</head>\n"
                                    "<body bgcolor=#ffffff link=#5000A0>\n"
                                        "<h1 style=\"text-align: center;\">"
                                        "<strong>                                                      "+TT+" </ strong>"


                                   //     "<align='right'> " << datefich << "</align>"
                                    "<center> <H1> Liste Des Emissions"
                                    " </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";


                                // headers
                                out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
                                for (int column = 0; column < columnCount; column++)
                                    if (!ui->show_emission->isColumnHidden(column))
                                        out << QString("<th>%1</th>").arg(ui->show_emission->model()->headerData(column, Qt::Horizontal).toString());
                                out << "</tr></thead>\n";

                                // data table
                                for (int row = 0; row < rowCount; row++) {
                                    out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
                                    for (int column = 0; column < columnCount; column++) {
                                        if (!ui->show_emission->isColumnHidden(column)) {
                                            QString data = ui->show_emission->model()->data(ui->show_emission->model()->index(row, column)).toString().simplified();
                                            out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                        }
                                    }
                                    out << "</tr>\n";
                                }
                                out <<  "</table> </center>\n"
                                    "</body>\n"
                                    "</html>\n";


                                QTextDocument *document = new QTextDocument();
                                document->setHtml(strStream);
                                QPrinter printer;

                                QPrintDialog *dialog = new QPrintDialog(&printer, nullptr);
                                if (dialog->exec() == QDialog::Accepted) {
                                    document->print(&printer);
                                }


                                delete document;
}

void Emp::on_XL_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                        tr("Excel Files (*.xls)"));
        if (fileName.isEmpty())
            return;

        ExportExcelObject obj(fileName, "mydata", ui->show_emission);

        //colums to export
        obj.addField(0, "ID", "char(20)");
        obj.addField(1, "NOM", "char(20)");
        obj.addField(2, "DATED", "char(20)");
        obj.addField(3, "DATEF", "char(20)");



        int retVal = obj.export2Excel();
        if( retVal > 0)
        {
            QMessageBox::information(this, tr("Done"),
                                     QString(tr("%1 records exported!")).arg(retVal)
                                     );
        }
}




void Emp::on_ajout_4_clicked()
{
    int ID=ui->li_id->text().toInt();
    QString NOM=ui->li_nom->text();
    QString DATED=ui->li_dated->text();
    QString DATEF =ui->li_datef->text();

    emission E (ID,NOM,DATED,DATEF);
    bool test=E.ajouter();

            if(test)
                {
                QMessageBox::information(nullptr,QObject::tr("Ok"),
                                     QObject::tr("Ajout effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                  ui->show_emission->setModel(E.afficher());

                }
            else
                {
                QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                                     QObject::tr("Ajout non effectué\n"
                                                   "Click cancel to exit."),QMessageBox::Cancel);
                }
}

void Emp::on_modifier_4_clicked()
{
    int ID=ui->li_id->text().toInt();
    QString NOM=ui->li_nom->text();
    QString DATED=ui->li_dated->text();
   QString DATEF=ui->li_datef->text();



emission E (ID,NOM,DATED,DATEF);


    bool test=E.modifier();
    if(test)

        {
        QMessageBox::information(nullptr,QObject::tr("Ok"),
        QObject::tr("Modification effectuée\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);


        ui->show_emission->setModel(E.afficher());

        }
    else
        {
        QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                             QObject::tr("Modification non effectuée\n"
                                           "Click cancel to exit."),QMessageBox::Cancel);

        }
}

void Emp::on_Supprimer_4_clicked()
{
    int ID =ui->li_id->text().toInt();
     emission E (ID);
     bool test=E.supprimer(ID);
   if (test)
   {

       QMessageBox::information(nullptr,QObject::tr("Ok"),
                            QObject::tr("suppression effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       ui->show_emission->setModel(E.afficher());

       }
   else
       {
       QMessageBox::critical(nullptr,QObject::tr("Not ok"),
                            QObject::tr("suppression non effectué\n"
                                          "Click cancel to exit."),QMessageBox::Cancel);
       }
}

void Emp::on_chercher_4_clicked()
{
    emission E;
    QString choix;
             choix=ui->li_chercher->text();
             QString li_chercher=ui->li_chercher->text();
             ui->show_emission->setModel(E.chercher_emission(li_chercher));
}

void Emp::on_tri_nom_4_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_nom());
}

void Emp::on_qr_5_clicked()
{
    if(ui->show_emission->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                            QObject::tr("Veuillez Choisir un identifiant.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int li_id=ui->show_emission->model()->data(ui->show_emission->model()->index(ui->show_emission->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(li_id).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                    QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    svgRenderer.render( &pixPainter );
                    ui->QRCODE->setPixmap(pix);

               }
}



void Emp::on_EmissionPassed_clicked()
{
    app=new CToDoList();
       app->show();
}
void   Emp::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_7->clear();
    ui->subject_7->clear();
    ui->file_3->clear();
    ui->msg_7->clear();
    ui->mail_pass_7->clear();
}
void Emp::on_browseBtn_7_clicked()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file_3->setText( fileListString );
}

void Emp::on_sendMail_clicked()
{

        Smtp* smtp = new Smtp("aziz.bouzidi@esprit.tn",ui->mail_pass_7->text(), "smtp.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        if( !files.isEmpty() )
            smtp->sendMail("aziz.bouzidi@esprit.tn", ui->rcpt_7->text() , ui->subject_7->text(),ui->msg_7->toPlainText(), files );
        else
            smtp->sendMail("aziz.bouzidi@esprit.tn", ui->rcpt_7->text() , ui->subject_7->text(),ui->msg_7->toPlainText());
}


void Emp::on_calendarWidget_selectionChanged()
{
    ui->dateEdit_5->setDate(ui->calendarWidget->selectedDate());
}

//
