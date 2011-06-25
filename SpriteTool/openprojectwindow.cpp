#include "openprojectwindow.h"
#include "ui_openprojectwindow.h"

#include <QDebug>

#include "maincontroller.h"

cOpenProjectWindow::cOpenProjectWindow(cMainController *parent) :
    QDialog(parent->get_main_window_ref()),
    ui(new Ui::cOpenProjectWindow)
{
  ui->setupUi(this);

  m_controller = parent;

  setWindowTitle("Open Project");
  setModal(true);

  connect(ui->btn_ok,SIGNAL(clicked()),this,SLOT(ok_clicked()));
  connect(ui->btn_cancel,SIGNAL(clicked()),this,SLOT(cancel_clicked()));
}

cOpenProjectWindow::~cOpenProjectWindow()
{
  delete ui;
}

void cOpenProjectWindow::add_sprite_option(QString s)
{
  ui->cb_sprite->addItem(s);
}

void cOpenProjectWindow::ok_clicked()
{
  m_controller->create_sprite(ui->cb_sprite->currentText());

  close();
}

void cOpenProjectWindow::cancel_clicked()
{
  close();
}
