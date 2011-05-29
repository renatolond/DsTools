#include "newprojectdialog.h"
#include "ui_newprojectdialog.h"

#include "mainwindow.h"
#include <QMessageBox>

#include "globaldata.h"

cNewProjectDialog::cNewProjectDialog(sGlobalData *global_data, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::cNewProjectDialog)
{
  ui->setupUi(this);
  connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(validate()));
  m_global_data = global_data;
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
    error_msg.exec();
    return;
  }
  if(x % m_global_data->tile_width)
  {
    QMessageBox error_msg;
    error_msg.setText("A largura do background tem que ser multipla de " +
                      QString::number(m_global_data->tile_width) + ".");
    error_msg.exec();
    return;
  }
  if(y % m_global_data->tile_height)
  {
    QMessageBox error_msg;
    QString msg = "A altura do background tem que ser múltipla de " +
        QString::number(m_global_data->tile_height) + ".";
    error_msg.setText(trUtf8(msg.toAscii()));
    error_msg.exec();
    return;
  }
  if(num_layers == 0)
  {
    QMessageBox error_msg;
    error_msg.setText("O projeto precisa ter pelo menos uma camada de background");
    error_msg.exec();
    return;
  }

  MainWindow *p = (MainWindow *)parent();
  p->create_level(project_name, num_layers, x, y);
  accept();
}

void cNewProjectDialog::on_buttonBox_rejected()
{

}

void cNewProjectDialog::validate()
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
}
