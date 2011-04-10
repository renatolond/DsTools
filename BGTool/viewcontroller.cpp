#include "viewcontroller.h"

#include "background.h"
#include "globaldata.h"
#include "spritesgraphicsview.h"

#include <QColor>
#include <QImage>
#include <QPixmap>

cViewController::cViewController(void)
{
  m_background = NULL;
  m_editor_view = NULL;
  m_global_data = NULL;
  m_palette_view = NULL;
  m_selected_sprite_view = NULL;
  m_sprites_view = NULL;

  m_selected_sprite = -1;

  m_sprites_per_column = 4;
}

void cViewController::set_background(cBackground *background)
{
  m_background = background;
  set_global_data(m_background->m_global_data);
}

void cViewController::set_editor_view(VisualizationGraphicsView *editor_view)
{
  m_editor_view = editor_view;
}

void cViewController::set_global_data(sGlobalData *global_data)
{
  m_global_data = global_data;
}

void cViewController::set_palette_view(QGraphicsView *palette_view)
{
  m_palette_view = palette_view;
}

void cViewController::set_selected_sprite_view(QGraphicsView *selected_sprite_view)
{
  m_selected_sprite_view = selected_sprite_view;
}

void cViewController::set_sprites_view(SpritesGraphicsView *sprites_view)
{
  m_sprites_view = sprites_view;
}

void cViewController::update_editor_view(void)
{

}

void cViewController::update_palette_view(void)
{

}

void cViewController::update_selected_sprite_view(void)
{
  const QVector<QImage *> &sprites = m_background->get_sprites();

  if(m_selected_sprite == -1)
    m_selected_sprite = sprites.size()-1;

  int pixel_width = m_selected_sprite_view->width() / m_global_data->sprite_width;
  int pixel_height = m_selected_sprite_view->height() / m_global_data->sprite_height;

  int pixel_size = pixel_width;
  if(pixel_height < pixel_size)
    pixel_size = pixel_height;

  QImage selected_sprite = QImage(pixel_size*sprite_width, pixel_size*sprite_height,
                                  QImage::Format_Indexed8);

  selected_sprite.setColorTable(m_background->get_palette());
  QColor neutral_without_alpha(selected_sprite.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  selected_sprite.setColor(0, neutral_without_alpha.rgb()); // Tirando o canal alpha da primeira cor


  for(int i(0); i < m_global_data->sprite_height; ++i)
  {
    for(int j(0); j < m_global_data->sprite_width; ++j)
    {
      for(int m(0); m < pixel_size; ++m)
        for(int n(0); n < pixel_size; ++n)
          selected_sprite.setPixel(j*pixel_size+n, i*pixel_size+m,
                                   sprites[m_selected_sprite]->pixelIndex(j, i));
    }
  }

  QPixmap selected_sprite_pixmap = QPixmap::fromImage(selected_sprite);
  m_selected_sprite_view->setSceneRect(selected_sprite_pixmap.rect());
  QGraphicsScene *scene = m_selected_sprite_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_selected_sprite_view);
    m_selected_sprite_view->setScene(scene);
  }
  scene->addPixmap(selected_sprite_pixmap);
  m_selected_sprite_view->show();
}

void cViewController::update_sprites_view(void)
{
  const QVector<QImage *> &sprites = m_background->get_sprites();

  m_sprites_per_row = (sprites.size()/m_sprites_per_column);
  if(sprites.size() % m_sprites_per_column)
    ++m_sprites_per_row;

  int sprite_grid_width, sprite_grid_height;
  sprite_grid_width = m_global_data->sprite_width * m_sprites_per_column +
                      m_sprites_per_column * m_global_data->grid_width;

  sprite_grid_height = m_global_data->sprite_height * m_sprites_per_row +
                      m_sprites_per_row * m_global_data->grid_heigth;


  QImage sprite_grid = QImage(sprite_grid_width, sprite_grid_height, QImage::Format_Indexed8);

  sprite_grid.setColorTable(m_background->get_palette());

  QColor neutral_without_alpha(sprite_grid.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  sprite_grid.setColor(0, neutral_without_alpha.rgb()); // Tirando o canal alpha da primeira cor

  sprite_grid.setColorCount(sprite_grid.colorCount()+1); // criando uma cor nova, por default e
                                                         // transparente
  sprite_grid.fill(sprite_grid.colorCount()-1);

  {
    int row, column;
    row = column = 0;

    for(int i(0); i < sprites.size(); ++i)
    {
      for(int n(0); n < m_global_data->sprite_height; ++n)
      {
        for(int m(0); m < m_global_data->sprite_width; ++m)
        {
          int sprite_grid_column, sprite_grid_row;
          sprite_grid_column = (m_global_data->sprite_width+m_global_data->grid_width)*column + m;
          sprite_grid_row = (m_global_data->sprite_height+m_global_data->grid_heigth)*row + n;

          sprite_grid.setPixel(sprite_grid_column, sprite_grid_row, sprites[i]->pixelIndex(m, n));
        }
      }


      ++column;
      if(column == m_sprites_per_column)
      {
        column = 0;
        ++row;
      }
    }
  }

  QPixmap sprite_grid_pixmap = QPixmap::fromImage(sprite_grid);
  m_sprites_view->setSceneRect(sprite_grid_pixmap.rect());
  QGraphicsScene *scene = m_sprites_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_sprites_view);
    m_sprites_view->setScene(scene);
  }
  scene->addPixmap(sprite_grid_pixmap);
  m_sprites_view->show();
}

void cViewController::update_views(void)
{
  if(m_background && m_global_data)
  {
    if(m_editor_view)
      update_editor_view();
    if(m_palette_view)
      update_palette_view();
    if(m_selected_sprite_view)
      update_selected_sprite_view();
    if(m_sprites_view)
      update_sprites_view();
  }
}
