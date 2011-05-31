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
#include "tiles_graphics_view.h"
#include "visualizationgraphicsview.h"
// End of Project libraries

cViewController::cViewController(void)
{
  m_background = NULL;
  m_editor_view = NULL;
  m_global_data = NULL;
  m_palette_view = NULL;
  m_selected_tile_rect = NULL;
  m_selected_tile_view = NULL;
  m_tiles_view = NULL;

  m_selected_tile_index = -1;

  m_selected_tile_vflip = false;
  m_selected_tile_hflip = false;

  m_tiles_per_row = 4;
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

void cViewController::set_selected_tile_view(QGraphicsView *selected_tile_view)
{
  m_selected_tile_view = selected_tile_view;
}

void cViewController::set_tiles_view(cTilesGraphicsView *tile_view)
{
  m_tiles_view = tile_view;
  m_tiles_view->set_view_controller(this);
}

void cViewController::update_editor_view(void)
{
  const QVector< QVector<sMapInfo> > &map_matrix = m_background->get_map_matrix();
  const QVector<sTileInfo> &tiles = m_background->get_tiles();

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
      QImage* tile = tiles[current.m_tile_index].m_tile;
      QImage transformed_tile;

      if(current.m_tile_flipping == HORIZONTAL_FLIPPING)
      {
        transformed_tile = tile->transformed(QTransform().scale(-1, 1));
      }
      else if(current.m_tile_flipping == VERTICAL_FLIPPING)
      {
        transformed_tile = tile->transformed(QTransform().scale(1, -1));
      }
      else if(current.m_tile_flipping == VERTICAL_AND_HORIZONTAL_FLIPPING)
      {
        transformed_tile = tile->transformed(QTransform().scale(-1, -1));
      }
      else
      {
        transformed_tile = QImage(*tile);
      }

      for(int m(0); m < m_global_data->tile_height; ++m)
      {
        for(int n(0); n < m_global_data->tile_width; ++n)
        {
          int editor_grid_row = (m_global_data->tile_height+m_global_data->grid_height)*i + m;
          int editor_grid_column = (m_global_data->tile_width+m_global_data->grid_width)*j + n;

          editor_grid.setPixel(editor_grid_column, editor_grid_row,
                               transformed_tile.pixelIndex(n, m));
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

void cViewController::update_selected_tile_view(void)
{
  const QVector<sTileInfo> &tiles = m_background->get_tiles();

  if(m_selected_tile_index == -1)
    m_selected_tile_index = tiles.size()-1;

  QImage original_selected_tile;
  {
    int transform_x, transform_y;
    transform_x = transform_y = 1;
    if(m_selected_tile_vflip)
      transform_y = -1;
    if(m_selected_tile_hflip)
      transform_x = -1;
    original_selected_tile =
        tiles[m_selected_tile_index].m_tile->transformed(QTransform().scale(transform_x,
                                                                            transform_y));
  }


  int pixel_width = m_selected_tile_view->width() / m_global_data->tile_width;
  int pixel_height = m_selected_tile_view->height() / m_global_data->tile_height;

  int pixel_size = pixel_width;
  if(pixel_height < pixel_size)
    pixel_size = pixel_height;

  QImage selected_tile = QImage(pixel_size*m_global_data->tile_width,
                                  pixel_size*m_global_data->tile_height,
                                  QImage::Format_Indexed8);

  selected_tile.setColorTable(m_background->get_palette());
  QColor neutral_without_alpha(selected_tile.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  selected_tile.setColor(0, neutral_without_alpha.rgb()); // Taking off alpha channel from the
                                                            // first color


  for(int i(0); i < m_global_data->tile_height; ++i)
  {
    for(int j(0); j < m_global_data->tile_width; ++j)
    {
      for(int m(0); m < pixel_size; ++m)
        for(int n(0); n < pixel_size; ++n)
          selected_tile.setPixel(j*pixel_size+n, i*pixel_size+m,
                                   original_selected_tile.pixelIndex(j, i));
    }
  }

  QPixmap selected_tile_pixmap = QPixmap::fromImage(selected_tile);
  m_selected_tile_view->setSceneRect(selected_tile_pixmap.rect());
  QGraphicsScene *scene = m_selected_tile_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_selected_tile_view);
    m_selected_tile_view->setScene(scene);
  }
  scene->addPixmap(selected_tile_pixmap);
  m_selected_tile_view->show();
}

void cViewController::update_tiles_view(void)
{
  const QVector<sTileInfo> &tiles = m_background->get_tiles();

  m_tiles_per_column = (tiles.size()/m_tiles_per_row);
  if(tiles.size() % m_tiles_per_row)
    ++m_tiles_per_column;

  int tile_grid_width, tile_grid_height;
  tile_grid_width = m_global_data->tile_width * m_tiles_per_row +
      m_tiles_per_row * m_global_data->grid_width;

  tile_grid_height = m_global_data->tile_height * m_tiles_per_column +
      m_tiles_per_column * m_global_data->grid_height;


  QImage tile_grid = QImage(tile_grid_width, tile_grid_height, QImage::Format_Indexed8);

  tile_grid.setColorTable(m_background->get_palette());

  QColor neutral_without_alpha(tile_grid.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  tile_grid.setColor(0, neutral_without_alpha.rgb()); // Taking off alpha channel from the first
                                                        // color
  tile_grid.setColorCount(tile_grid.colorCount()+1); // create a new color. By default it is
                                                         // transparent
  tile_grid.fill(tile_grid.colorCount()-1);

  {
    int row, column;
    row = column = 0;

    for(int i(0); i < tiles.size(); ++i)
    {
      for(int n(0); n < m_global_data->tile_height; ++n)
      {
        for(int m(0); m < m_global_data->tile_width; ++m)
        {
          int tile_grid_column, tile_grid_row;
          tile_grid_column = (m_global_data->tile_width+m_global_data->grid_width)*column + m;
          tile_grid_row = (m_global_data->tile_height+m_global_data->grid_height)*row + n;

          tile_grid.setPixel(tile_grid_column, tile_grid_row, tiles[i].m_tile->pixelIndex(m, n));
        }
      }


      ++column;
      if(column == m_tiles_per_row)
      {
        column = 0;
        ++row;
      }
    }
  }

  QPixmap tile_grid_pixmap = QPixmap::fromImage(tile_grid);
  m_tiles_view->setSceneRect(tile_grid_pixmap.rect());
  QGraphicsScene *scene = m_tiles_view->scene();
  if(!scene)
  {
    scene = new QGraphicsScene(m_tiles_view);
    m_tiles_view->setScene(scene);
  }
  scene->addPixmap(tile_grid_pixmap);
  m_tiles_view->show();
}

void cViewController::update_views(void)
{
  if(m_background && m_global_data)
  {
    if(m_editor_view)
      update_editor_view();
    if(m_palette_view)
      update_palette_view();
    if(m_selected_tile_view)
      update_selected_tile_view();
    if(m_tiles_view)
      update_tiles_view();
  }
}

void cViewController::tiles_view_clicked(int x, int y)
{
  if(!m_tiles_view)
    return;

  QGraphicsScene *scene = m_tiles_view->scene();

  // If the user clicks over an already existing rect, we remove the rect
  if(QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(scene->itemAt(x, y)))
  {
    scene->removeItem(r);
    m_selected_tile_rect = NULL;
    m_selected_tile_index = -1;
    update_selected_tile_view();
    return;
  }

  QGraphicsPixmapItem *tiles_pixmap = dynamic_cast<QGraphicsPixmapItem *>(scene->itemAt(x, y));
  // If the user clicks outside the pixmap, or over something we don't know how to treat, we return
  // TODO(renatolond, 2011-05-08) If is something we don't know how to treat, we should do something
  // maybe log what it was.
  if(!tiles_pixmap)
    return;

  int selected_tile_view_x, selected_tile_view_y;
  int selected_tile_index;
  {
    int selected_tile_x, selected_tile_y;
    get_tile_coords_from_view_coords(x, y, selected_tile_x, selected_tile_y);
    get_view_coords_from_tile_coords(selected_tile_x, selected_tile_y, selected_tile_view_x,
                                       selected_tile_view_y);
    selected_tile_index = (selected_tile_y*m_tiles_per_row) + selected_tile_x;
  }

  const QVector<sTileInfo> &tiles = m_background->get_tiles();

  // If the size of the tiles vector is not greater than the selected tile index, then we
  // clicked on an empty space within the tiles pixmap
  if(tiles.size() <= selected_tile_index)
    return;

  // We already had an tile selected, this means we have to remove the rectangle around it, in
  // order to put a new onde around the one we clicked.
  if(m_selected_tile_rect != NULL)
  {
    scene->removeItem(m_selected_tile_rect);
    m_selected_tile_rect = NULL;
  }

  m_selected_tile_index = selected_tile_index;
  update_selected_tile_view();

  QPen pen;
  pen.setColor(Qt::yellow);
  pen.setWidth(2);
  scene->addRect(selected_tile_view_x, selected_tile_view_y, m_global_data->tile_width,
                 m_global_data->tile_height, pen);
  m_selected_tile_rect = dynamic_cast<QGraphicsRectItem *>(scene->itemAt(selected_tile_view_x,
                                                                           selected_tile_view_y));
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

void cViewController::highlight_selected_tile(void)
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

  if(m_selected_tile_index < 0)
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

  const QVector<sTileInfo> &tiles = m_background->get_tiles();
  const QVector<QRgb> &palette = m_background->get_palette();
  int map_x, map_y;

  get_tile_coords_from_view_coords(x, y, map_x, map_y);

  sAction *action = new sAction();
  action->type = sAction::PAINT;
  action->x = x;
  action->y = y;
  action->n_x = map_x;
  action->n_y = map_y;

  eTileFlipping map_flipping;
  if(m_selected_tile_vflip && m_selected_tile_hflip)
    map_flipping = VERTICAL_AND_HORIZONTAL_FLIPPING;
  else if(m_selected_tile_vflip)
    map_flipping = VERTICAL_FLIPPING;
  else if(m_selected_tile_hflip)
    map_flipping = HORIZONTAL_FLIPPING;
  else
    map_flipping = NO_FLIPPING;
  // TODO(renatolond, 20-04-2011) Take flipping into account
  m_background->set_map_matrix(map_x, map_y, m_selected_tile_index, map_flipping);

  QImage original_selected_tile;
  {
    int transform_x, transform_y;
    transform_x = transform_y = 1;
    if(m_selected_tile_vflip)
      transform_y = -1;
    if(m_selected_tile_hflip)
      transform_x = -1;
    original_selected_tile =
        tiles[m_selected_tile_index].m_tile->transformed(QTransform().scale(transform_x,
                                                                            transform_y));
  }

  // Painter actions
  // TODO(renatolond, 2011-05-30) Fix alpha for showing.
//  bit_mask_painter.begin(&bit_mask);
  {
    for(int i(0); i < m_global_data->tile_height; ++i)
    {
      for(int j(0); j < m_global_data->tile_width; ++j)
      {
        int color_index = original_selected_tile.pixelIndex(j, i);
        QColor color = QColor::fromRgba(palette[color_index]);

        get_view_coords_from_tile_coords(map_x, map_y, x, y);

        // Here we draw the alpha mask of visualizationGrid.
        //if(color.alpha() != 255)
          //bit_mask_painter.setPen(Qt::color0);
        //else
          //bit_mask_painter.setPen(Qt::color1);

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

void cViewController::get_tile_coords_from_view_coords(int x, int y, int &map_x, int &map_y)
{
  map_x = x/(m_global_data->tile_width+m_global_data->grid_width);
  map_y = y/(m_global_data->tile_height+m_global_data->grid_height);
}

void cViewController::get_view_coords_from_tile_coords(int map_x, int map_y, int &x, int &y)
{
  x = map_x*(m_global_data->tile_width+m_global_data->grid_width);
  y = map_y*(m_global_data->tile_height+m_global_data->grid_height);
}

void cViewController::set_selected_tile_hflip(bool status)
{
  m_selected_tile_hflip = status;
  update_selected_tile_view();
}

void cViewController::set_selected_tile_vflip(bool status)
{
  m_selected_tile_vflip = status;
  update_selected_tile_view();
}
