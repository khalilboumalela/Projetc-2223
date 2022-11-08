#ifndef EMP_H
#define EMP_H

#include <QDialog>


#include "employes.h"
namespace Ui {
class Emp;
}

class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class QVBoxLayout;
class QMenu;
class QAction;

class Emp : public QDialog
{
    Q_OBJECT

public:
    explicit Emp(QWidget *parent = nullptr);
    ~Emp();

private slots:
    void on_ajouter_clicked();

    void on_supprimer_clicked();



    void on_modifier_clicked();

    //void on_modifier_toggled(bool checked);

    void on_modifier_2_clicked();

    void on_Tri_cin_clicked();

    void on_Tri_nom_clicked();

    void on_Tri_fonct_clicked();

    void on_Recherche_clicked();

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

};

#endif // EMP_H
