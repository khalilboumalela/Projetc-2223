#include "mainwindow.h"
#include "ui_mainwindow.h"
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




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Connection C;
        C.createconnection();
        connect(ui->sendMail, SIGNAL(clicked()),this, SLOT(sendMail()));
        connect(ui->browseBtn_7, SIGNAL(clicked()), this, SLOT(browse()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_emission_activated(const QModelIndex &index)
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







void MainWindow::on_tri_date_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_dated());
}

void MainWindow::on_tri_datef_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_datef());
}






void MainWindow::on_pdf_clicked()
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

void MainWindow::on_XL_clicked()
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




void MainWindow::on_ajout_4_clicked()
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

void MainWindow::on_modifier_4_clicked()
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

void MainWindow::on_Supprimer_4_clicked()
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

void MainWindow::on_chercher_4_clicked()
{
    emission E;
    QString choix;
             choix=ui->li_chercher->text();
             QString li_chercher=ui->li_chercher->text();
             ui->show_emission->setModel(E.chercher_emission(li_chercher));
}

void MainWindow::on_tri_nom_4_clicked()
{
    emission E ;
    ui->show_emission->setModel(E.afficher_tri_nom());
}

void MainWindow::on_qr_5_clicked()
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



void MainWindow::on_EmissionPassed_clicked()
{
    app=new CToDoList();
       app->show();
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt_7->clear();
    ui->subject_7->clear();
    ui->file_3->clear();
    ui->msg_7->clear();
    ui->mail_pass_7->clear();
}
void MainWindow::on_browseBtn_7_clicked()
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

void MainWindow::on_sendMail_clicked()
{

        Smtp* smtp = new Smtp("aziz.bouzidi@esprit.tn",ui->mail_pass_7->text(), "smtp.gmail.com");
        connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

        if( !files.isEmpty() )
            smtp->sendMail("aziz.bouzidi@esprit.tn", ui->rcpt_7->text() , ui->subject_7->text(),ui->msg_7->toPlainText(), files );
        else
            smtp->sendMail("aziz.bouzidi@esprit.tn", ui->rcpt_7->text() , ui->subject_7->text(),ui->msg_7->toPlainText());
}


void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->dateEdit_5->setDate(ui->calendarWidget->selectedDate());
}
