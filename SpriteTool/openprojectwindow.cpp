#include "openprojectwindow.h"
#include "ui_openprojectwindow.h"

#include <QDebug>

OpenProjectWindow::OpenProjectWindow(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::OpenProjectWindow)
{
    ui->setupUi(this);

    pai = parent;

    this->setWindowTitle("Open Project");
    this->setModal(true);

    connect(ui->btnOk,SIGNAL(clicked()),this,SLOT(okClicked()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancelClicked()));
}

OpenProjectWindow::~OpenProjectWindow()
{
    delete ui;
}

void OpenProjectWindow::addSpriteOption(QString s)
{
    ui->cbSprite->addItem(s);
}

void OpenProjectWindow::okClicked()
{
    qDebug() << ui->cbSprite->currentText();

    pai->createSprite(ui->cbSprite->currentText());

    this->close();
}

void OpenProjectWindow::cancelClicked()
{
    this->close();
}
