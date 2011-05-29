#include "viewcontroller.h" // Class definition

// QT libraries
#include <QBitmap>
#include <QColor>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
// End of QT libraries

// Project libraries
#include "background.h"
#include "globaldata.h"
#include "spritesgraphicsview.h"
#include "visualizationgraphicsview.h"
// End of Project libraries

cViewController::cViewController(void)
{
  m_background = NULL;
  m_editor_view = NULL;
  m_global_data = NULL;
  m_palette_view = NULL;
  m_selected_sprite_rect = NULL;
  m_selected_sprite_view = NULL;
  m_sprites_view = NULL;

  m_selected_sprite_index = -1;

  m_selected_sprite_vflip = false;
  m_selected_sprite_hflip = false;

  m_sprites_per_row = 4;
}

void cViewController::set_background(cBackground *background)
{
  m_background = background;
  set_global_data(m_background->m_global_data);
}

void cViewController::set_editor_view(VisualizationGraphicsView *editor_view)
{
  m_editor_view = editor_view;
  m_editor_view->set_view_controller(this);
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
  m_sprites_view->set_view_controller(this);
}

void cViewController::update_editor_view(void)
{
  const QVector< QVector<sMapInfo> > &map_matrix = m_background->get_map_matrix();
  const QVector<QImage *> &sprites = m_background->get_tiles();

  int editor_grid_height = map_matrix.size() * m_global_data->tile_height +
      map_matrix.size() * m_global_data->grid_height;
  int editor_grid_width = map_matrix[0].size() * m_global_data->tile_width +
      map_matrix[0].size() * m_global_data->grid_width;

  QImage editor_grid = QImage(editor_grid_width, editor_grid_height, QImage::Format_Indexed8);
  editor_grid.setColorTable(m_background->get_palette());
  editor_grid.fill(0);

  for(int i(0); i < map_matrix.size(); ++i)
  {
    for(int j(0); j < map_matrix[i].size(); ++j)
    {
      sMapInfo current = map_matrix[i][j];
      QImage* sprite = sprites[current.m_tile_index];
      QImage transformed_sprite;

      if(current.m_tile_flipping == HORIZONTAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(-1, 1));
      }
      else if(current.m_tile_flipping == VERTICAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(1, -1));
      }
      else if(current.m_tile_flipping == VERTICAL_AND_HORIZONTAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(-1, -1));
      }
      else
      {
        transformed_sprite = QImage(*sprite);
      }

      for(int m(0); m < m_global_data->tile_height; ++m)
      {
        for(int n(0); n < m_global_data->tile_width; ++n)
        {
          int editor_grid_row = (m_global_data->tile_height+m_global_data->grid_height)*i + m;
          int editor_grid_column = (m_global_data->tile_width+m_global_data->grid_width)*j + n;

          editor_grid.setPixel(editor_grid_column, editor_grid_row,
                               transformed_sprite.pixelIndex(n, m));
        }
      }
    }
  }

  QPixmap editor_grid_pixmap = QPixmap::fromImage(editor_grid);
  m_editor_view->setSceneRect(editor_grid_pixmap.rect());
  QGraphicsScene *scene = m_editor_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_editor_view);
    m_editor_view->setScene(scene);
  }
  scene->addPixmap(editor_grid_pixmap);
  m_editor_view->show();
}

void cViewController::update_palette_view(void)
{
  const QVector<QRgb> &palette = m_background->get_palette();
  int row, column;
  const int color_width = 8;
  const int color_height = 8;

  int colors_per_column = 8;
  int colors_per_row = palette.size() / colors_per_column;
  if(palette.size() % colors_per_column)
    ++colors_per_row;

  row = column = 0;

  int palette_grid_height = color_height*colors_per_row + colors_per_row*m_global_data->grid_height;
  int palette_grid_width = color_width * colors_per_column +
      colors_per_column * m_global_data->grid_width;

  QImage palette_grid = QImage(palette_grid_width, palette_grid_height, QImage::Format_Indexed8);
  palette_grid.setColorTable(palette);
  QColor neutral_without_alpha(palette_grid.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  palette_grid.setColor(0, neutral_without_alpha.rgb()); // Taking off alpha channel from the
                                                         // first color
  palette_grid.setColorCount(palette_grid.colorCount()+1); // create a new color, by default it is
                                                           // transparent
  palette_grid.fill(palette_grid.colorCount()-1);

  for(int i(0); i < palette.size(); ++i)
  {
    for(int m(0); m < color_height; ++m)
    {
      for(int n(0); n < color_width; ++n)
      {
        int palette_grid_row = (color_height+m_global_data->grid_height)*row + n;
        int palette_grid_column = (color_width+m_global_data->grid_width)*column + m;

        palette_grid.setPixel(palette_grid_column, palette_grid_row, i);
      }
    }

    ++column;
    if(column == colors_per_column)
    {
      column = 0;
      ++row;
    }
  }

  QPixmap palette_grid_pixmap = QPixmap::fromImage(palette_grid);
  m_palette_view->setSceneRect(palette_grid_pixmap.rect());
  QGraphicsScene *scene = m_palette_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_palette_view);
    m_palette_view->setScene(scene);
  }
  scene->addPixmap(palette_grid_pixmap);
  m_palette_view->show();
}

void cViewController::update_selected_sprite_view(void)
{
  const QVector<QImage *> &sprites = m_background->get_tiles();

  if(m_selected_sprite_index == -1)
    m_selected_sprite_index = sprites.size()-1;

  QImage original_selected_sprite;
  {
    int transform_x, transform_y;
    transform_x = transform_y = 1;
    if(m_selected_sprite_vflip)
      transform_y = -1;
    if(m_selected_sprite_hflip)
      transform_x = -1;
    original_selected_sprite =
        sprites[m_selected_sprite_index]->transformed(QTransform().scale(transform_x, transform_y));
  }


  int pixel_width = m_selected_sprite_view->width() / m_global_data->tile_width;
  int pixel_height = m_selected_sprite_view->height() / m_global_data->tile_height;

  int pixel_size = pixel_width;
  if(pixel_height < pixel_size)
    pixel_size = pixel_height;

  QImage selected_sprite = QImage(pixel_size*m_global_data->tile_width,
                                  pixel_size*m_global_data->tile_height,
                                  QImage::Format_Indexed8);

  selected_sprite.setColorTable(m_background->get_palette());
  QColor neutral_without_alpha(selected_sprite.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  selected_sprite.setColor(0, neutral_without_alpha.rgb()); // Taking off alpha channel from the
                                                            // first color


  for(int i(0); i < m_global_data->tile_height; ++i)
  {
    for(int j(0); j < m_global_data->tile_width; ++j)
    {
      for(int m(0); m < pixel_size; ++m)
        for(int n(0); n < pixel_size; ++n)
          selected_sprite.setPixel(j*pixel_size+n, i*pixel_size+m,
                                   original_selected_sprite.pixelIndex(j, i));
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
  const QVector<QImage *> &sprites = m_background->get_tiles();

  m_sprites_per_column = (sprites.size()/m_sprites_per_row);
  if(sprites.size() % m_sprites_per_row)
    ++m_sprites_per_column;

  int sprite_grid_width, sprite_grid_height;
  sprite_grid_width = m_global_data->tile_width * m_sprites_per_row +
      m_sprites_per_row * m_global_data->grid_width;

  sprite_grid_height = m_global_data->tile_height * m_sprites_per_column +
      m_sprites_per_column * m_global_data->grid_height;


  QImage sprite_grid = QImage(sprite_grid_width, sprite_grid_height, QImage::Format_Indexed8);

  sprite_grid.setColorTable(m_background->get_palette());

  QColor neutral_without_alpha(sprite_grid.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  sprite_grid.setColor(0, neutral_without_alpha.rgb()); // Taking off alpha channel from the first
                                                        // color
  sprite_grid.setColorCount(sprite_grid.colorCount()+1); // create a new color. By default it is
                                                         // transparent
  sprite_grid.fill(sprite_grid.colorCount()-1);

  {
    int row, column;
    row = column = 0;

    for(int i(0); i < sprites.size(); ++i)
    {
      for(int n(0); n < m_global_data->tile_height; ++n)
      {
        for(int m(0); m < m_global_data->tile_width; ++m)
        {
          int sprite_grid_column, sprite_grid_row;
          sprite_grid_column = (m_global_data->tile_width+m_global_data->grid_width)*column + m;
          sprite_grid_row = (m_global_data->tile_height+m_global_data->grid_height)*row + n;

          sprite_grid.setPixel(sprite_grid_column, sprite_grid_row, sprites[i]->pixelIndex(m, n));
        }
      }


      ++column;
      if(column == m_sprites_per_row)
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

void cViewController::sprites_view_clicked(int x, int y)
{
  if(!m_sprites_view)
    return;

  QGraphicsScene *scene = m_sprites_view->scene();

  // If the user clicks over an already existing rect, we remove the rect
  if(QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(scene->itemAt(x, y)))
  {
    scene->removeItem(r);
    m_selected_sprite_rect = NULL;
    m_selected_sprite_index = -1;
    update_selected_sprite_view();
    return;
  }

  QGraphicsPixmapItem *sprites_pixmap = dynamic_cast<QGraphicsPixmapItem *>(scene->itemAt(x, y));
  // If the user clicks outside the pixmap, or over something we don't know how to treat, we return
  // TODO(renatolond, 2011-05-08) If is something we don't know how to treat, we should do something
  // maybe log what it was.
  if(!sprites_pixmap)
    return;

  int selected_sprite_view_x, selected_sprite_view_y;
  int selected_sprite_index;
  {
    int selected_sprite_x, selected_sprite_y;
    get_sprite_coords_from_view_coords(x, y, selected_sprite_x, selected_sprite_y);
    get_view_coords_from_sprite_coords(selected_sprite_x, selected_sprite_y, selected_sprite_view_x,
                                       selected_sprite_view_y);
    selected_sprite_index = (selected_sprite_y*m_sprites_per_row) + selected_sprite_x;
  }

  const QVector<QImage *> &sprites = m_background->get_tiles();

  // If the size of the sprites vector is not greater than the selected sprite index, then we
  // clicked on an empty space within the sprites pixmap
  if(sprites.size() <= selected_sprite_index)
    return;

  // We already had an sprite selected, this means we have to remove the rectangle around it, in
  // order to put a new onde around the one we clicked.
  if(m_selected_sprite_rect != NULL)
  {
    scene->removeItem(m_selected_sprite_rect);
    m_selected_sprite_rect = NULL;
  }

  m_selected_sprite_index = selected_sprite_index;
  update_selected_sprite_view();

  QPen pen;
  pen.setColor(Qt::yellow);
  pen.setWidth(2);
  scene->addRect(selected_sprite_view_x, selected_sprite_view_y, m_global_data->tile_width,
                 m_global_data->tile_height, pen);
  m_selected_sprite_rect = dynamic_cast<QGraphicsRectItem *>(scene->itemAt(selected_sprite_view_x,
                                                                           selected_sprite_view_y));
}

void cViewController::editor_view_clicked(int x, int y)
{
  if(m_paint_mode)
  {
    editor_view_clicked_paint(x, y);
  }
}

void cViewController::set_paint_mode(bool status)
{
  m_paint_mode = status;
}

void cViewController::dump_map_matrix(void)
{

}

void cViewController::export_to_png(void)
{
}

void cViewController::export_background(void)
{
  m_background->export_to_ds();
}

void cViewController::highlight_selected_sprite(void)
{

}

void cViewController::turn_off_highlight(void)
{

}

void cViewController::editor_view_clicked_paint(int x, int y)
{
  if(!m_editor_view)
    return;
  QGraphicsScene *scene = m_editor_view->scene();
  if(!scene)
    return;

  if(m_selected_sprite_index < 0)
    return;

  QGraphicsPixmapItem *editor_pixmap_item;
  {
    QGraphicsItem* item = scene->itemAt(x, y);
    if(!item)
      return;

    editor_pixmap_item = dynamic_cast<QGraphicsPixmapItem *>(item);
    if(!editor_pixmap_item)
      return;
  }

  QPixmap editor_pixmap = editor_pixmap_item->pixmap();
  QImage editor_image = editor_pixmap.toImage();

  QBitmap bit_mask = QBitmap(editor_pixmap.mask());
  QPainter bit_mask_painter;

  const QVector<QImage *> &sprites = m_background->get_tiles();
  const QVector<QRgb> &palette = m_background->get_palette();
  int map_x, map_y;

  get_sprite_coords_from_view_coords(x, y, map_x, map_y);

  sAction *action = new sAction();
  action->type = sAction::PAINT;
  action->x = x;
  action->y = y;
  action->n_x = map_x;
  action->n_y = map_y;

  eTileFlipping map_flipping;
  if(m_selected_sprite_vflip && m_selected_sprite_hflip)
    map_flipping = VERTICAL_AND_HORIZONTAL_FLIPPING;
  else if(m_selected_sprite_vflip)
    map_flipping = VERTICAL_FLIPPING;
  else if(m_selected_sprite_hflip)
    map_flipping = HORIZONTAL_FLIPPING;
  else
    map_flipping = NO_FLIPPING;
  // TODO(renatolond, 20-04-2011) Take flipping into account
  m_background->set_map_matrix(map_x, map_y, m_selected_sprite_index, map_flipping);

  QImage original_selected_sprite;
  {
    int transform_x, transform_y;
    transform_x = transform_y = 1;
    if(m_selected_sprite_vflip)
      transform_y = -1;
    if(m_selected_sprite_hflip)
      transform_x = -1;
    original_selected_sprite =
        sprites[m_selected_sprite_index]->transformed(QTransform().scale(transform_x, transform_y));
  }

  // Painter actions
//  bit_mask_painter.begin(&bit_mask);
  {
    for(int i(0); i < m_global_data->tile_height; ++i)
    {
      for(int j(0); j < m_global_data->tile_width; ++j)
      {
        int color_index = original_selected_sprite.pixelIndex(j, i);
        QColor color = QColor::fromRgba(palette[color_index]);

        get_view_coords_from_sprite_coords(map_x, map_y, x, y);

        // Here we draw the alpha mask of visualizationGrid.
        if(color.alpha() != 255)
          bit_mask_painter.setPen(Qt::color0);
        else
          bit_mask_painter.setPen(Qt::color1);

        //bit_mask_painter.drawPoint(x+j, y+i);
        editor_image.setPixel(x+j, y+i, color.rgb());
      }
    }
  }
  //bit_mask_painter.end();

  editor_pixmap = QPixmap::fromImage(editor_image);
  //editor_pixmap.setMask(bit_mask);
  editor_pixmap_item->setPixmap(editor_pixmap);
}

void cViewController::get_sprite_coords_from_view_coords(int x, int y, int &map_x, int &map_y)
{
  map_x = x/(m_global_data->tile_width+m_global_data->grid_width);
  map_y = y/(m_global_data->tile_height+m_global_data->grid_height);
}

void cViewController::get_view_coords_from_sprite_coords(int map_x, int map_y, int &x, int &y)
{
  x = map_x*(m_global_data->tile_width+m_global_data->grid_width);
  y = map_y*(m_global_data->tile_height+m_global_data->grid_height);
}

void cViewController::set_selected_sprite_hflip(bool status)
{
  m_selected_sprite_hflip = status;
  update_selected_sprite_view();
}

void cViewController::set_selected_sprite_vflip(bool status)
{
  m_selected_sprite_vflip = status;
  update_selected_sprite_view();
}
