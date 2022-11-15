#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "smtp.h"
#include <QFileInfo>
#include "todolist.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_show_emission_activated(const QModelIndex &index);



    void on_tri_date_clicked();

    void on_tri_datef_clicked();


    void mailSent(QString status);

    void on_pdf_clicked();

    void on_XL_clicked();

    void on_ajout_4_clicked();

    void on_modifier_4_clicked();

    void on_Supprimer_4_clicked();

    void on_chercher_4_clicked();

    void on_tri_nom_4_clicked();

    void on_qr_5_clicked();

    void on_EmissionPassed_clicked();

    void on_browseBtn_7_clicked();

    void on_sendMail_clicked();

    void on_calendarWidget_selectionChanged();

private:
    Ui::MainWindow *ui;
    QStringList files;
     CToDoList *app;

};

#endif // MAINWINDOW_H
