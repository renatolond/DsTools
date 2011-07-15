#include "drawing_tab.h" // Class definition

// QT libraries
#include <QFileDialog>
// End of QT libraries

// Project libraries
#include "background.h"
#include "viewcontroller.h"
#include "ui_drawing_tab.h"
// End of Project libraries

cDrawingTab::cDrawingTab(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::cDrawingTab)
{
  m_background = NULL;
  m_view_controller = NULL;
  ui->setupUi(this);
  index = -1;
}
void cDrawingTab::setIndex(int i)
{
  index = i;
}

cDrawingTab::~cDrawingTab()
{
  delete ui;
}

void cDrawingTab::changeEvent(QEvent *e)
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

void cDrawingTab::on_btConvert_clicked()
{
  if(m_background == NULL)
    return;

  QString filename = QFileDialog::getOpenFileName(this, QObject::tr("Open Image..."), "./",
                                                  QObject::tr("Images (*.png *.xpm *.jpg)"));
  if ( filename == "" ) return;

  m_background->import_image(filename);

  m_view_controller->update_views();
}

void cDrawingTab::on_btPaint_toggled(bool checked)
{
  m_view_controller->set_paint_mode(checked);
}

void cDrawingTab::on_btExportPng_clicked()
{
  m_view_controller->export_to_png();
}

void cDrawingTab::on_btExport_clicked()
{
  m_view_controller->export_background();
}

void cDrawingTab::on_btHighlight_toggled(bool checked)
{
  if(checked)
    m_view_controller->highlight_selected_tile();
  else
    m_view_controller->turn_off_highlight();
}

void cDrawingTab::set_background(cBackground *background)
{
  m_background = background;

  m_view_controller = new cViewController();
  m_view_controller->set_background(m_background);
  m_view_controller->set_editor_view(ui->visualizationView);
  m_view_controller->set_palette_view(ui->paletteView);
  m_view_controller->set_selected_tile_view(ui->selectedView);
  m_view_controller->set_tiles_view(ui->tilesView);

  m_view_controller->update_views();
}

void cDrawingTab::on_bt_hflip_toggled(bool checked)
{
  m_view_controller->set_selected_tile_hflip(checked);
}

void cDrawingTab::on_bt_vflip_toggled(bool checked)
{
  m_view_controller->set_selected_tile_vflip(checked);
}

void cDrawingTab::export_background()
{
  m_view_controller->export_background();
}
