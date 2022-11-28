#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_seconnecter_clicked();

    void on_oublie_clicked();

    void on_creercmpt_clicked();

  /*  void on_nomut_in2_cursorPositionChanged(int arg1, int arg2);

    void on_mdp_in2_cursorPositionChanged(int arg1, int arg2);

    void on_mdp_in3_cursorPositionChanged(int arg1, int arg2);

    void on_Adresse_in_cursorPositionChanged(int arg1, int arg2);

    void on_nomut_in_cursorPositionChanged(int arg1, int arg2);

    void on_mdp_in_cursorPositionChanged(int arg1, int arg2);

    void on_mdp_3_linkHovered(const QString &link);*/

    void on_Scan_clicked();

    void on_seconnecter_3_clicked();

private:
    Ui::MainWindow *ui;
       Arduino A;
};
#endif // MAINWINDOW_H
