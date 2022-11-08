#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "emp.h"
#include <QMessageBox>
#include "connection.h"
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
    FILE *f;
    int tst=0;
    QString Name,Mdp;
    f=fopen("Users.bin","wb");

    while (!feof(f) && tst==0)
{fread(&Name,sizeof (QString),1,f);
        fread(&Mdp,sizeof (QString),1,f);
        if ((ui->nomut_in->text()==Name) && (ui->mdp_in->text()==Mdp)) tst++;
    }
    if (((ui->nomut_in->text()=="khalil") && (ui->mdp_in->text()=="khalil")) || (tst!=0))
{
        bool test=true;
        c.createconnect();
        if(test)
        {
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("connection successful.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

    }
        else
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("connection failed.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);

        e.exec();

    }
    else {

        QMessageBox::critical(nullptr, QObject::tr("Password incorrect"),
                           QObject::tr("Please check your password or try again later.\n"
                                       ), QMessageBox::Cancel);

    }

}

void MainWindow::on_oublie_clicked()
{
    QMessageBox::critical(nullptr, QObject::tr("ERROR"),
                QObject::tr("Contact your administrator.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_creercmpt_clicked()
{
    FILE *f;
    f=fopen("Users.bin","ab");
    QString Name,Mdp;

   if ((ui->nomut_in2->text()!="") && (ui->mdp_in2->text()!=""))
    {while (!feof(f) )
{
        fwrite( &Name, sizeof(QString), 1, f);
        fwrite(&Mdp,sizeof(QString), 1, f);
    }
   }
}
