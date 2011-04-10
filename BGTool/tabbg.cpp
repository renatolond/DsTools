#include "tabbg.h"
#include "ui_tabbg.h"

#include <QFileDialog>

#include "background.h"
#include "viewcontroller.h"

TabBG::TabBG(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TabBG)
{
  m_background = NULL;
  m_view_controller = NULL;
  ui->setupUi(this);
//  ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
  index = -1;
}
void TabBG::setIndex(int i)
{
  index = i;
//  imgData->index = i;
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
  if(m_background == NULL)
    return;

  QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Open Image..."), "./",
                                                  QObject::tr("Images (*.png *.xpm *.jpg)"));
  if ( filename == "" ) return;

  m_background->import_image(filename);

//  if ( imgData != 0 )
//  {
//    delete imgData;
//    imgData = 0;
//  }

//  imgData = new imagesData(QImage(),QImage());
//  imgData->index = this->index;
//  ui->spritesView->imgData = ui->visualizationView->imgData = imgData;
//  imgData->importPng(ui->visualizationView, ui->spritesView, ui->selectedView, ui->paletteView,
//                     filename);
  m_view_controller = new cViewController();
  m_view_controller->set_background(m_background);
  m_view_controller->set_editor_view(ui->visualizationView);
  m_view_controller->set_palette_view(ui->paletteView);
  m_view_controller->set_selected_sprite_view(ui->selectedView);
  m_view_controller->set_sprites_view(ui->spritesView);

  m_view_controller->update_views();
}

void TabBG::on_btPaint_toggled(bool checked)
{
  ui->visualizationView->btPaintPressed = checked;
}

void TabBG::on_btDump_clicked()
{
//  imgData->dumpBgMatrix();
}

void TabBG::on_btHighlight_clicked()
{
}

void TabBG::on_btExportPng_clicked()
{
//  imgData->exportPng();
}

void TabBG::on_btExport_clicked()
{
//  imgData->exportBG();
}

void TabBG::on_btHighlight_toggled(bool checked)
{
//  imgData->highlightSelectedSprite(checked);
}

void TabBG::set_background(cBackground *background)
{
  m_background = background;
}
