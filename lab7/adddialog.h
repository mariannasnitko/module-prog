#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <inventor.h>

namespace Ui
{
class AddDialog;
}

class AddDialog : public QDialog
{
    Q_OBJECT

  public:
    explicit AddDialog(QWidget *parent = 0);
    ~AddDialog();
    Inventor createNewInventor();

  private:
    Ui::AddDialog *ui;
};

#endif // ADDDIALOG_HPP