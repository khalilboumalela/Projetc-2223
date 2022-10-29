#ifndef EMP_H
#define EMP_H

#include <QDialog>
#include "employes.h"
namespace Ui {
class Emp;
}

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

private:
    Ui::Emp *ui;
    employes e;
};

#endif // EMP_H
