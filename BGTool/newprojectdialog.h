#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
    class cNewProjectDialog;
}

struct sGlobalData;

class cNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cNewProjectDialog(sGlobalData *global_data, QWidget *parent = 0);
    ~cNewProjectDialog();

private slots:
  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

  void validate();
private:
    Ui::cNewProjectDialog *ui;
    sGlobalData *m_global_data;
};

#endif // NEWPROJECTDIALOG_H
