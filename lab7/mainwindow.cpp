#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#include "inventor.h"
#include "storage.h"
#include "csv_storage.h"
#include "editdialog.h"
#include "adddialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->centralWidget->setEnabled(false);
    ui->formLayoutWidget->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete this->storage_;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    AddDialog dialog(this);
    dialog.setWindowTitle("Adding new inventor");
    if (dialog.exec())
    {
        Inventor inv = dialog.createNewInventor();
        int newInventorId = this->storage_->insertInventor(inv);
        inv.id = newInventorId;
        QVariant qVariant;
        qVariant.setValue(inv);
        QListWidgetItem *qInvListItem = new QListWidgetItem();
        qInvListItem->setText(QString::fromStdString(inv.name));
        qInvListItem->setData(Qt::UserRole, qVariant);
        ui->listWidget->addItem(qInvListItem);
        this->storage_->save();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    auto item = ui->listWidget->selectedItems().at(0);
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(
        this,
        "Delete item",
                "Are you sure?",
        QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        QVariant var = item->data(Qt::UserRole);
        Inventor inv = var.value<Inventor>();
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
        if (ui->listWidget->count() == 0)
        {
            ui->formLayoutWidget->setVisible(false);
        }
        else
        {
            this->on_listWidget_itemClicked(ui->listWidget->selectedItems().at(0));
        }
        this->storage_->removeInventor(inv.id);
        this->storage_->save();
        if (ui->listWidget->count() == 0)
        {
            ui->formLayoutWidget->setVisible(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    EditDialog dialog(this);
    dialog.setWindowTitle("Editing");
    QVariant var = ui->listWidget->selectedItems().at(0)->data(Qt::UserRole);
    Inventor inv = var.value<Inventor>();
    dialog.setDefault(inv);
    if (dialog.exec())
    {
        const Inventor updInv = dialog.editInventor(inv);
        this->storage_->updateInventor(updInv);
        this->storage_->save();
        QVariant qVariant;
        qVariant.setValue(updInv);
        ui->listWidget->selectedItems().at(0)->setText(QString::fromStdString(updInv.name));
        ui->listWidget->selectedItems().at(0)->setData(Qt::UserRole, qVariant);
        this->on_listWidget_itemClicked(ui->listWidget->selectedItems().at(0));
    }
}

void MainWindow::on_actionNew_storage_triggered()
{
    if (this->storage_ != nullptr)
    {
        ui->listWidget->clear();
        ui->formLayoutWidget->setVisible(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        delete this->storage_;
    }
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    QString current_dir = QDir::currentPath();
    QString default_name = "csv_storage";
    QString folder_path = dialog.getSaveFileName(
        this,
        "Select New Storage Folder",
        current_dir + "/" + default_name,
        "Folders");

    QDir().mkdir(folder_path);
    CsvStorage *newCsvSt = new CsvStorage(folder_path.toStdString());
    this->storage_ = newCsvSt;
    this->storage_->save();
    ui->centralWidget->setEnabled(true);
}

void MainWindow::on_actionOpen_storage_triggered()
{
    if (this->storage_ != nullptr)
    {
        ui->listWidget->clear();
        ui->formLayoutWidget->setVisible(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        delete this->storage_;
    }
    QString directoryName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                              "/home",
                                                              QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (QDir(directoryName).exists() == false)
    {
        QDir().mkdir(directoryName);
        CsvStorage *newCsvSt = new CsvStorage(directoryName.toStdString());
        this->storage_ = newCsvSt;
        this->storage_->save();
    }
    else
    {
        CsvStorage *newCsvSt = new CsvStorage(directoryName.toStdString());
        this->storage_ = newCsvSt;
        this->storage_->load();
        vector<Inventor> inventors = this->storage_->getAllInventors();
        for (auto i : inventors)
        {
            QVariant qVariant;
            qVariant.setValue(i);
            QListWidgetItem *qInvListItem = new QListWidgetItem();
            qInvListItem->setText(QString::fromStdString(i.name));
            qInvListItem->setData(Qt::UserRole, qVariant);
            ui->listWidget->addItem(qInvListItem);
        }
    }
    ui->centralWidget->setEnabled(true);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->formLayoutWidget->setVisible(true);
    QVariant var = item->data(Qt::UserRole);
    Inventor in = var.value<Inventor>();

    ui->label_2->setText(QString::fromStdString(in.name));
    ui->label_4->setText(QString::fromStdString(in.invention));
    ui->label_6->setText(QString::number(in.patents));
    ui->label_8->setText(QString::number(in.id));
}
