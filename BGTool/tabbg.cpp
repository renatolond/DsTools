#include "tabbg.h"
#include "ui_tabbg.h"

TabBG::TabBG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabBG)
{
    ui->setupUi(this);
    imgData = new imagesData(QImage(),QImage());
    ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
}

TabBG::~TabBG()
{
    delete ui;
}

void TabBG::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void TabBG::on_btConvert_clicked()
{
    imgData->importPng(ui->visualizationView, ui->spritesView, ui->selectedView);
//    statusBar()->showMessage("File loaded.",10*1000);
}

void TabBG::on_btPaint_toggled(bool checked)
{
    ui->visualizationView->btPaintPressed = checked;
}

void TabBG::on_btDump_clicked()
{
    imgData->dumpBgMatrix();
}

void TabBG::on_btHighlight_clicked()
{
    imgData->highlightSelectedSprite();
}

void TabBG::on_btExportPng_clicked()
{
    imgData->exportPng();
}
