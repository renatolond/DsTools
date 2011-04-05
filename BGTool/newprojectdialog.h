#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
    class cNewProjectDialog;
}

class cNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cNewProjectDialog(QWidget *parent = 0);
    ~cNewProjectDialog();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

  void validate();
private:
    Ui::cNewProjectDialog *ui;
};

#endif // NEWPROJECTDIALOG_H
