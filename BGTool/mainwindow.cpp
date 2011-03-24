#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "project.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->widget0->setIndex(0);
    ui->widget1->setIndex(1);
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
    if ( index == 0 )
        ui->widget_all->completeImgData(ui->widget0->imgData, ui->widget1->imgData);
}

void MainWindow::on_actionNew_Project_triggered()
{
  if(m_project != NULL)
  {
    // Mostra um alerta, dizendo ao usuário que continuar irá destruir o projeto atual
  }

  m_project = new cProject();
}
