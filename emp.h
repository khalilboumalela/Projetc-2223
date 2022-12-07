#ifndef EMP_H
#define EMP_H

#include <QDialog>
#include <QDataStream>
//**Equipements**
#include "employes.h"
#include "arduino.h"
#include "equipement.h"
//
//*******Reclamations****
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include "reclamation.h"
#include "smtp.h"
#include <QPrinter>

//
//***Spons**
#include "sponsor.h"

//****Emiss****
#include <QMainWindow>
#include "smtp.h"
#include <QFileInfo>
#include "todolist.h"
//

namespace Ui {
class Emp;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;
class QMediaPlayer;

class Emp : public QDialog
{
    Q_OBJECT

public:
    explicit Emp(QWidget *parent = nullptr);
    ~Emp();

private slots:
    //************Gestion Employés***********//
    void on_ajouter_clicked();

    void on_supprimer_clicked();



    void on_modifier_clicked();

    //void on_modifier_toggled(bool checked);

    void on_modifier_2_clicked();

    void on_Tri_cin_clicked();

    void on_Tri_nom_clicked();

    void on_Tri_fonct_clicked();

    void on_Recherche_clicked();

    void on_l_r_2_cursorPositionChanged(int arg1, int arg2);

    void on_tabWidget_currentChanged(int index);

    void on_PDF_clicked();

    void on_Imprimer_clicked();

    void on_Emp_2_currentChanged(int index);


    //***Gestion Equipements*********


    void update_label();
void on_pB_AjouterP_clicked();

void on_pB_ModifierP_clicked();

void on_pB_SupprimerP_clicked();

void on_pB_TirerParReff_clicked();

void on_pB_TireParNom_clicked();

void on_pB_TirerParQuantite_clicked();

void on_pB_Recherche_clicked();

void on_comboBox_currentIndexChanged(int index);

void on_pB_export_pdf_clicked();

void on_pB_Stats_clicked();

void on_pB_Map_clicked();

void on_pushButton_Fermer_clicked();

void on_pB_excel_clicked();


    //************Gestion Réclamations********
    void on_pb_ajouter_clicked();

  void on_pb_modifier_clicked();

   void on_pb_supprimer_clicked();

   void on_pb_play_vid_clicked();

   void on_pb_stop_vid_clicked();

   void browse();

   void update_label2();

   void on_button_trier_clicked();

   void on_pdf_clicked();

   void on_image_clicked();

   void on_radioButton_clicked();

   void on_stat_clicked();

   void on_recherche_textChanged();


//
   //******Sponsors*****
   void on_pb_ajouter_2_clicked();



   void on_pb_supprimer_2_clicked();




//void on_le_code2_cursorPositionChanged(int arg1, int arg2);

void on_pb_modifier_2_clicked();

void on_pushButton_9_clicked();

//void on_tab_sponsor_activated(const QModelIndex &index);

//void on_le_code_supp_cursorPositionChanged(int arg1, int arg2);
//void on_image_clicked();



//void on_pdf_clicked();

//void on_pushButton_clicked();

void on_pushButton_2_clicked();

void on_pushButton_12_clicked();
//void on_pushButtonqrcode_clicked();

//void on_qrcodegen_clicked();


void on_on_btn_2_image_clicked();
//
//****Emissions***
void on_show_emission_activated(const QModelIndex &index);



    void on_tri_date_clicked();

    void on_tri_datef_clicked();


    void mailSent(QString status);

    void on_pdf_2_clicked();

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

//

private:
    Ui::Emp *ui;
    employes e;
    QCamera *mCamera;
    QCameraViewfinder *mCameraViewfinder;
    QCameraImageCapture *mCameraImageCapture;
    QVBoxLayout *m;
    QMenu *mOptionsmenu;
    QAction *mOuvrir;
    QAction *mCapturer;
    QAction *mSauv;
    Arduino A;
    //Equipp
 equipement E;
    QByteArray data;

    QMediaPlayer *mMediaPlayer;
    QTimer *Timer;
//
    // Reclam
    QMediaPlayer* player;
        QVideoWidget* vw;
        int selected=0;
          QStringList files;
          reclamation RE;
    //
          //Spons
          Sponsor S;
          Sponsor Etmp;
          //
//Emiss**
          QStringList filess;
               CToDoList *app;
          //
};

#endif // EMP_H
