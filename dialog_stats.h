#ifndef DIALOG_STATS_H
#define DIALOG_STATS_H
#include "QtPrintSupport"
#include <QDialog>

namespace Ui {
class Dialog_Stats;
}

class Dialog_Stats : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Stats(QWidget *parent = nullptr);
    ~Dialog_Stats();

private slots:
    void on_pushButton_Fermer_clicked();

private:
    Ui::Dialog_Stats *ui;
    void MakeStat();
    void statistiques(QVector<double>* ticks,QVector<QString> *labels);
};

#endif // DIALOG_STATS_H
