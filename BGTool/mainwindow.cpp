#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imgData = new imagesData(QImage(),QImage());
    ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
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

void MainWindow::on_btConvert_clicked()
{
    imgData->importPng(ui->visualizationView, ui->spritesView, ui->selectedView);
    statusBar()->showMessage("File loaded.",10*1000);
}

void MainWindow::on_btPaint_toggled(bool checked)
{
    ui->visualizationView->btPaintPressed = checked;
}

void MainWindow::on_btDump_clicked()
{
    imgData->dumpBgMatrix();
}

void MainWindow::on_btHighlight_clicked()
{
    imgData->highlightSelectedSprite();
}

void MainWindow::on_btExportPng_clicked()
{
    imgData->exportPng();
}
