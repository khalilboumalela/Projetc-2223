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
    if ((ui->nomut_in->text()=="") && (ui->mdp_in->text()==""))
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
