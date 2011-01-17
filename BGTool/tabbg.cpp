#include "tabbg.h"
#include "ui_tabbg.h"

TabBG::TabBG(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TabBG)
{
    ui->setupUi(this);
    imgData = new imagesData(QImage(),QImage());
    ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
    index = -1;
}
void TabBG::setIndex(int i)
{
    index = i;
    imgData->index = i;
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
    if ( imgData != 0 )
    {
	delete imgData;
	imgData = 0;
    }

    imgData = new imagesData(QImage(),QImage());
    imgData->index = this->index;
    ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
    QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Open Image..."), "./", QObject::tr("Images (*.png *.xpm *.jpg)"));
    if ( filename != "" )
	imgData->importPng(ui->visualizationView, ui->spritesView, ui->selectedView, ui->paletteView, filename);
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

void TabBG::on_btExport_clicked()
{
    imgData->exportBG();
}
