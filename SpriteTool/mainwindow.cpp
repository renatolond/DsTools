#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "newprojectwindow.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDataStream>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sprite.clear();

    this->disable();

    connect(ui->btn_NewProject,SIGNAL(clicked()),this,SLOT(newProject()));
    connect(ui->btn_SaveProject,SIGNAL(clicked()),this,SLOT(saveProject()));
    connect(ui->btn_OpenProject,SIGNAL(clicked()),this,SLOT(openProject()));
    connect(ui->btn_CloseProject,SIGNAL(clicked()),this,SLOT(closeProject()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::disable(void)
{
    ui->btn_NewProject->setEnabled(true);
    ui->btn_OpenProject->setEnabled(true);

    ui->btn_AddFrame->hide();

    ui->btn_SaveProject->setDisabled(true);
    ui->btn_CloseProject->setDisabled(true);
}

void MainWindow::enable(void)
{
    ui->btn_NewProject->setDisabled(true);
    ui->btn_OpenProject->setDisabled(true);

    ui->btn_AddFrame->show();

    ui->btn_SaveProject->setEnabled(true);
    ui->btn_CloseProject->setEnabled(true);
}

void MainWindow::newProject()
{
   NewProjectWindow np(this);

   np.exec();

   qDebug() << "Leu " << sprite.getNome() << " ("
            << sprite.getWidth() << "x" << sprite.getHeight() << ")";
}

void MainWindow::closeProject()
{
    sprite.clear();
    disable();
}

void MainWindow::saveProject()
{
    QString filename = QFileDialog::getSaveFileName(this,
                            tr("Salvar Projeto"),"",
                            tr("Arquivos XML (*.xml);;All Files (*)"));

    // colocar um path default em ""

    if (filename.isEmpty())
        return;

    QFile* file = new QFile(filename);

    if (!file->open(QIODevice::ReadOnly))
    {
        QMessageBox::information(this, tr("Não foi possível acessar o arquivo."),file->errorString());
        return;
    }

    qDebug() << "file: " << filename;

    if (file!= NULL)
        qDebug() << "BELEZA TEREZA";
    else
        qDebug() << "i like turtles";

    QDomDocument doc("xmldocument");

    if (!doc.setContent(file))
    {
        QMessageBox::information(this, tr("Erro no arquivo XML."),file->errorString());
        return;
    }



    QDomElement docElem = doc.documentElement();

    qDebug() << "Tag docElem" << docElem.tagName();

    // só to tentando escrever a tag da raiz pra começar a busca.


    file->close();
}

void MainWindow::openProject()
{
    // se o documento puder ter varios sprites lá, como escolher qual abrir? combobox

}

void MainWindow::createSprite(QString nome, int w, int h)
{
    this->sprite = Sprite(nome,w,h);

    this->enable();
}

void MainWindow::on_btn_AddFrame_clicked()
{

}
