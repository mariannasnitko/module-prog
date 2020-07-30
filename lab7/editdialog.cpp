#include "editdialog.h"
#include "ui_editdialog.h"

EditDialog::EditDialog(QWidget *parent) : QDialog(parent),
                                          ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::setDefault(const Inventor &inv)
{
    ui->lineEdit->setText(QString().fromStdString(inv.name));
    ui->lineEdit_2->setText(QString().fromStdString(inv.invention));
    ui->spinBox->setValue(inv.patents);
    ui->spinBox_2->setValue(inv.id);
}

Inventor EditDialog::editInventor(Inventor inv)
{
    QString input = ui->lineEdit->text();
    inv.name = input.toStdString();
    QString input2 = ui->lineEdit_2->text();
    inv.invention = input2.toStdString();
    inv.patents = ui->spinBox->value();
    inv.id = ui->spinBox_2->value();
    return inv;
}
