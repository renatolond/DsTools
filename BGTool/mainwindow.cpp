#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "project.h"
#include "level.h"
#include "drawing_tab.h"
#include "newprojectdialog.h"
#include "globaldata.h"
#include "level.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  m_project = NULL;
  m_global_data = new sGlobalData();
  m_global_data->neutral_red = 255;
  m_global_data->neutral_blue = 255;
  m_global_data->neutral_green = 0;
  m_global_data->tile_height = 8;
  m_global_data->tile_width = 8;
  m_global_data->grid_height = 1;
  m_global_data->grid_width = 1;

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

  cNewProjectDialog new_project(m_global_data, this);
  new_project.exec();
}

void MainWindow::clear_active()
{
  if(m_project == NULL)
    return;
  cLevel *level = m_project->active_level();

  if(level == NULL)
    return;

  ui->tabWidget->setUpdatesEnabled(false);
  for(int i(level->num_layers()-1); i >= 0; --i)
  {
    delete m_tabbg_widgets[i];
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(m_tabs[i]));
    delete m_tabs[i];
  }
  ui->tabWidget->setUpdatesEnabled(true);
  m_project->delete_active_level();
}

void MainWindow::create_level(QString project_name, int num_layers, int x, int y)
{
  clear_active();
  m_project = new cProject(project_name);
  cLevel *level = new cLevel(project_name, num_layers, x, y, m_global_data);
  m_project->new_level(level);

  ui->tabWidget->setUpdatesEnabled(false);
  for(int i(0); i < num_layers ; ++i)
  {
    m_tabs[i] = new QWidget();
    m_tabbg_widgets[i] = new cDrawingTab(m_tabs[i]);
    m_tabbg_widgets[i]->set_background(level->get_background(i));
    ui->tabWidget->addTab(m_tabs[i], "BG"+QString::number(i));
  }
  ui->tabWidget->setUpdatesEnabled(true);
}

void MainWindow::on_actionClose_Project_triggered()
{
  clear_active();
}

void MainWindow::on_actionSave_Project_triggered()
{
  if(!m_project)
    return;

  QString filename = QFileDialog::getSaveFileName(this, tr("Save Project", "saveprojectfilename"),
                                                  "../"+m_project->get_project_name(),
                                                  tr("XML Files(*.xml);;All Files(*.*)"));
  m_project->export_to_xml(filename);
}

void MainWindow::on_actionOpen_Project_triggered()
{
  QString filename = QFileDialog::getOpenFileName(this, tr("Open Project", "openprojectfilename"),
                                                  "", tr("XML Files(*.xml);;All Files(*.*)"));

  clear_active();

  m_project = new cProject(filename,
                           m_global_data);

  cLevel *level = m_project->active_level();
  int num_layers = level->num_layers();

  ui->tabWidget->setUpdatesEnabled(false);
  for(int i(0); i < num_layers ; ++i)
  {
    m_tabs[i] = new QWidget();
    m_tabbg_widgets[i] = new cDrawingTab(m_tabs[i]);
    m_tabbg_widgets[i]->set_background(level->get_background(i));
    ui->tabWidget->addTab(m_tabs[i], "BG"+QString::number(i));
  }
  ui->tabWidget->setUpdatesEnabled(true);

}

void MainWindow::on_actionExport_All_triggered()
{
  for(int i(0); i < m_project->active_level()->num_layers(); ++i)
  {
    m_tabbg_widgets[i]->export_background();
  }
}
