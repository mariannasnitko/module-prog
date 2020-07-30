#include "adddialog.h"
#include "ui_adddialog.h"

AddDialog::AddDialog(QWidget *parent) : QDialog(parent),
                                        ui(new Ui::AddDialog)
{
    ui->setupUi(this);
}

AddDialog::~AddDialog()
{
    delete ui;
}

Inventor AddDialog::createNewInventor()
{
    Inventor newInv;
    QLineEdit *line1 = ui->lineEdit;
    QString lineEdit1 = line1->text();
    newInv.name = lineEdit1.toStdString();
    QLineEdit *line2 = ui->lineEdit_2;
    QString lineEdit2 = line2->text();
    newInv.invention = lineEdit2.toStdString();
    newInv.patents = ui->spinBox->value();
    newInv.id = ui->spinBox_2->value();
    return newInv;
}
