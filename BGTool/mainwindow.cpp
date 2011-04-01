#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"
#include "level.h"
#include "tabbg.h"
#include "newprojectdialog.h"
#include "globaldata.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  m_project = NULL;
  m_global_data = new sGlobalData();

  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
  QMainWindow::changeEvent(e);
  switch (e->type()) {
  case QEvent::LanguageChange:
    ui->retranslateUi(this);
    break;
  default:
    break;
  }
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
//  if ( index == 0 )
//    ui->widget_all->completeImgData(ui->widget0->imgData, ui->widget1->imgData);
}

void MainWindow::on_actionNew_Project_triggered()
{
  if(m_project != NULL)
  {
    // Mostra um alerta, dizendo ao usuário que continuar irá destruir o projeto atual
  }

  cNewProjectDialog new_project(this);
  new_project.exec();
}

void MainWindow::clear_active()
{
  if(m_project == NULL)
    return;
  cLevel *level = m_project->active_level();

  ui->tabWidget->setUpdatesEnabled(false);
  for(int i(level->num_layers()-1); i >= 0; --i)
  {
    delete m_tabbg_widgets[i];
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(m_tabs[i]));
    delete m_tabs[i];
  }
  ui->tabWidget->setUpdatesEnabled(true);
}

void MainWindow::create_level(QString project_name, int num_layers, int x, int y)
{
  clear_active();
  m_project = new cProject();
  cLevel *level = new cLevel(project_name, num_layers, x, y, m_global_data);
  m_project->new_level(level);

  ui->tabWidget->setUpdatesEnabled(false);
  for(int i(0); i < num_layers ; ++i)
  {
    m_tabs[i] = new QWidget();
    m_tabbg_widgets[i] = new TabBG(m_tabs[i]);
    ui->tabWidget->addTab(m_tabs[i], "BG"+QString::number(i));
  }
  ui->tabWidget->setUpdatesEnabled(true);
}
