#include "tabbg.h"// Class definition

// QT libraries
#include <QFileDialog>
// End of QT libraries

// Project libraries
#include "background.h"
#include "viewcontroller.h"
#include "ui_tabbg.h"
// End of Project libraries

TabBG::TabBG(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::TabBG)
{
  m_background = NULL;
  m_view_controller = NULL;
  ui->setupUi(this);
  index = -1;
}
void TabBG::setIndex(int i)
{
  index = i;
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
  m_view_controller->set_paint_mode(checked);
}

void TabBG::on_btDump_clicked()
{
  m_view_controller->dump_map_matrix();
}

void TabBG::on_btExportPng_clicked()
{
  m_view_controller->export_to_png();
}

void TabBG::on_btExport_clicked()
{
  m_view_controller->export_background();
}

void TabBG::on_btHighlight_toggled(bool checked)
{
  if(checked)
    m_view_controller->highlight_selected_sprite();
  else
    m_view_controller->turn_off_highlight();
}

void TabBG::set_background(cBackground *background)
{
  m_background = background;
}
