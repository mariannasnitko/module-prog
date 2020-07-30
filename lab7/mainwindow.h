#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "storage.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionNew_storage_triggered();

    void on_actionOpen_storage_triggered();

    void on_listWidget_itemClicked(QListWidgetItem *item);

  private:
    Ui::MainWindow *ui;
    Storage *storage_{nullptr};
};

#endif // MAINWINDOW_H
