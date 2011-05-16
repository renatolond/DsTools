#include "newprojectwindow.h"
#include "ui_newprojectwindow.h"

#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "sprite.h"

NewProjectWindow::NewProjectWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::NewProjectWindow)
{
    ui->setupUi(this);

    pai = parent;

    this->setWindowTitle("New Project");
    this->setModal(true);

    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(okClicked()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancelClicked()));

}

NewProjectWindow::~NewProjectWindow()
{
    delete ui;
}

void NewProjectWindow::okClicked()
{
   QString nome = ui->editNome->text();

   if (nome == "")
   {
       QMessageBox::information(this, tr("Erro!"),tr("É preciso entrar com um nome."));
       return;
   }

   QString tam = ui->comboBox->currentText();
   int w, h;

   QTextStream s(&tam,QIODevice::ReadOnly);

   s >> w >> " x " >> h;

   pai->createSprite(nome,w,h);

   this->close();

}

void NewProjectWindow::cancelClicked()
{
    ui->editNome->clear();
    this->close();
}



