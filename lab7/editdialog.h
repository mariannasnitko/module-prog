#ifndef EDITDIALOG_HPP
#define EDITDIALOG_HPP

#include <QDialog>
#include "inventor.h"

namespace Ui
{
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit EditDialog(QWidget *parent = 0);
    ~EditDialog();
    void setDefault(const Inventor &);
    Inventor editInventor(Inventor);

  private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_HPP
