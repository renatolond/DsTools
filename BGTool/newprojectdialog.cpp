#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include "mainwindow.h"
#include <QMessageBox>

cNewProjectDialog::cNewProjectDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::cNewProjectDialog)
{
  ui->setupUi(this);
}

cNewProjectDialog::~cNewProjectDialog()
{
  delete ui;
}

void cNewProjectDialog::on_buttonBox_accepted()
{
  int x, y;
  int num_layers;
  QString project_name;

  project_name = ui->ed_project_name->text();
  num_layers = ui->cb_layers->currentText().toInt();
  x = ui->ed_x->text().toInt();
  y = ui->ed_y->text().toInt();

  if((x <= 0) || (y <= 0))
  {
    QMessageBox error_msg;
    error_msg.setText("As medidas do background tem que ser maiores que zero.");
    return;
  }
  if(num_layers == 0)
  {
    QMessageBox error_msg;
    error_msg.setText("O projeto precisa ter pelo menos uma camada de background");
    return;
  }

  MainWindow *p = (MainWindow *)parent();
  p->create_level(project_name, num_layers, x, y);
  accepted();
}

void cNewProjectDialog::on_buttonBox_rejected()
{

}
