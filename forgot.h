#ifndef FORGOT_H
#define FORGOT_H

#include <QDialog>
#include "emp.h"

namespace Ui {
class Forgot;
}

class Forgot : public QDialog
{
    Q_OBJECT

public:
    explicit Forgot(QWidget *parent = nullptr);
    ~Forgot();

private slots:
    void on_Submit_clicked();

private:
    Ui::Forgot *ui;
    Emp e;
};

#endif // FORGOT_H
