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
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QTextDocument>
#include<QPdfWriter>
#include<QSystemTrayIcon>
#include<QPainter>
#include <QSettings>


Emp::Emp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Emp)
{
    ui->setupUi(this);
    ui->l_CIN->setValidator(new QIntValidator(0,999999999,this));
       ui->l_tel->setValidator(new QIntValidator(0,99999999,this));
       ui->l_salaire->setValidator(new QIntValidator(0,999999999,this));
       ui->tab_etud->setModel(e.afficher());

       /////////maps

       QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                          QCoreApplication::organizationName(), QCoreApplication::applicationName());

       ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");



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
    QPdfWriter pdf("C:/Users/khali/Downloads/C++/Projet_C++/liste.pdf");
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

