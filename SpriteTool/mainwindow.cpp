#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "maincontroller.h"
#include "newprojectwindow.h"
#include "openprojectwindow.h"

cMainWindow::cMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::cMainWindow)
{
  ui->setupUi(this);

  m_controller = new cMainController(this);

  reset();

  connect(ui->btn_NewProject,SIGNAL(clicked()),m_controller,SLOT(new_project()));
  connect(ui->btn_SaveProject,SIGNAL(clicked()),m_controller,SLOT(save_project()));
  connect(ui->btn_OpenProject,SIGNAL(clicked()),m_controller,SLOT(open_project()));
  connect(ui->btn_CloseProject,SIGNAL(clicked()),m_controller,SLOT(close_project()));
  connect(ui->btn_Right,SIGNAL(clicked()),this,SLOT(show_right()));
  connect(ui->btn_Left,SIGNAL(clicked()),this,SLOT(show_left()));
  connect(ui->btn_AddFrame,SIGNAL(clicked()),m_controller,SLOT(add_frame()));
  connect(ui->btn_DeleteFrame,SIGNAL(clicked()),m_controller,SLOT(del_frame()));
  connect(ui->btn_Animate,SIGNAL(clicked()),m_controller,SLOT(animate()));
  connect(ui->btn_Export,SIGNAL(clicked()),m_controller,SLOT(export_to_DS()));
}

cMainWindow::~cMainWindow()
{
    delete ui;
}

void cMainWindow::reset(void)
{
  ui->gv_Canvas->setParent(this);
  ui->gv_Canvas->setScene(m_controller->get_scene());

  disable();
}

void cMainWindow::disable(void)
{
    ui->btn_NewProject->setEnabled(true);
    ui->btn_OpenProject->setEnabled(true);

    ui->btn_AddFrame->hide();
    ui->btn_DeleteFrame->hide();
    ui->btn_Animate->hide();
    ui->btn_Right->hide();
    ui->btn_Left->hide();
    ui->btn_Export->hide();

    ui->btn_SaveProject->setDisabled(true);
    ui->btn_CloseProject->setDisabled(true);

}

void cMainWindow::enable(void)
{
    ui->btn_NewProject->setDisabled(true);
    ui->btn_OpenProject->setDisabled(true);

    ui->btn_AddFrame->show();
    ui->btn_DeleteFrame->show();
    ui->btn_Animate->show();
    ui->btn_Right->show();
    ui->btn_Left->show();
    ui->btn_Export->show();

    ui->btn_SaveProject->setEnabled(true);
    ui->btn_CloseProject->setEnabled(true);
}

void cMainWindow::show_frame(int i)
{
  m_controller->clear_scene();

  m_controller->add_frame_to_scene(i);

  ui->gv_Canvas->setScene(m_controller->get_scene());
  ui->gv_Canvas->show();

  manage_bounds();
}

void cMainWindow::show_left()
{
  m_controller->sub_current_frame();

  show_frame(m_controller->get_current_frame());

  manage_bounds();
}

void cMainWindow::show_right()
{
  m_controller->add_current_frame();;

  show_frame(m_controller->get_current_frame());

  manage_bounds();
}

void cMainWindow::manage_bounds()
{

  if(in_animation()) return;

  if(m_controller->get_current_frame() == -1)
  {
    ui->btn_DeleteFrame->setDisabled(true);
    ui->btn_Animate->setDisabled(true);
  }
  else
  {
    ui->btn_DeleteFrame->setEnabled(true);
    ui->btn_Animate->setEnabled(true);
  }

  if(m_controller->get_sprite_size() == 1)
  {
    ui->btn_Left->setDisabled(true);
    ui->btn_Right->setDisabled(true);

    return;
  }

  if(m_controller->get_current_frame() <= 0)
    ui->btn_Left->setDisabled(true);
  else
    ui->btn_Left->setEnabled(true);

  if(m_controller->get_current_frame() >= m_controller->get_sprite_size()-1)
    ui->btn_Right->setDisabled(true);
  else
    ui->btn_Right->setEnabled(true);
}

int cMainWindow::delete_procedure(int frame)
{
  // while deleting a frame that is on the canvas, go back a frame.
  // if the frame is the first one, go forward
  // if it is the only one, leave the canvas empty.
  // then, return the frame to be deleted position to the controller

  if(frame != 0)
  {
    show_left();
    return m_controller->get_current_frame()+1;
  }
  else if(m_controller->get_sprite_size() > 1)
  {
    show_right();
    return m_controller->get_current_frame()-1;
  }
  else            //only one frame
  {
    m_controller->reset_current_frame();
    return 0;
  }
}

void cMainWindow::set_animation_mode(void)
{
  ui->btn_Animate->setText("Stop");

  ui->btn_AddFrame->setDisabled(true);
  ui->btn_DeleteFrame->setDisabled(true);
  ui->btn_Right->setDisabled(true);
  ui->btn_Left->setDisabled(true);
  ui->btn_Export->setDisabled(true);

  ui->btn_NewProject->setDisabled(true);
  ui->btn_SaveProject->setDisabled(true);
  ui->btn_OpenProject->setDisabled(true);
  ui->btn_CloseProject->setDisabled(true);

}

void cMainWindow::set_edit_mode(void)
{
  ui->btn_Animate->setText("Animate");

  ui->btn_AddFrame->setEnabled(true);
  ui->btn_DeleteFrame->setEnabled(true);
  ui->btn_Right->setEnabled(true);
  ui->btn_Left->setEnabled(true);
  ui->btn_Export->setEnabled(true);

  ui->btn_NewProject->setEnabled(true);
  ui->btn_SaveProject->setEnabled(true);
  ui->btn_OpenProject->setEnabled(true);
  ui->btn_CloseProject->setEnabled(true);

}

bool cMainWindow::in_animation(void)
{
  if(ui->btn_Animate->text() == "Animate")
    return false;
  else
    return true;
}

void cMainWindow::call_manage_bounds(void)
{
  manage_bounds();
}
