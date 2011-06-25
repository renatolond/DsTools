#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

#include "sprite.h"
#include "maincontroller.h"

cNewProjectWindow::cNewProjectWindow(cMainController *parent) :
  QDialog(parent->get_main_window_ref()),
  ui(new Ui::cNewProjectWindow)
{
  ui->setupUi(this);

  m_controller = parent;

  setWindowTitle("New Project");
  setModal(true);

  connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));
  connect(ui->btn_cancel,SIGNAL(clicked()),this,SLOT(cancel_clicked()));

}

cNewProjectWindow::~cNewProjectWindow(void)
{
  delete ui;
}

void cNewProjectWindow::ok_clicked(void)
{
  QString nome = ui->edit_nome->text();

  if(nome == "")
  {
    QMessageBox::information(this, tr("Erro!"), tr("É preciso entrar com um nome."));
    return;
  }

  QString tam = ui->cb_sprite_size->currentText();
  int w, h;

  QTextStream s(&tam,QIODevice::ReadOnly);
  s >> w >> " x " >> h;

  m_controller->create_sprite(nome,w,h);

  close();
}

void cNewProjectWindow::cancel_clicked(void)
{
    ui->edit_nome->clear();
    close();
}



