#include "viewcontroller.h" // Class definition

// QT libraries
#include <QColor>
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
  const QVector< QVector<sSpriteInfo> > &map_matrix = m_background->get_map_matrix();
  const QVector<QImage *> &sprites = m_background->get_sprites();

  int editor_grid_height = map_matrix.size() * m_global_data->sprite_height +
      map_matrix.size() * m_global_data->grid_heigth;
  int editor_grid_width = map_matrix[0].size() * m_global_data->sprite_width +
      map_matrix[0].size() * m_global_data->grid_width;

  QImage editor_grid = QImage(editor_grid_width, editor_grid_height, QImage::Format_Indexed8);
  editor_grid.setColorTable(m_background->get_palette());
  editor_grid.fill(0);

  for(int i(0); i < map_matrix.size(); ++i)
  {
    for(int j(0); j < map_matrix[i].size(); ++j)
    {
      sSpriteInfo current = map_matrix[i][j];
      QImage* sprite = sprites[current.sprite_index];
      QImage transformed_sprite;

      if(current.sprite_flipping == HORIZONTAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(-1, 1));
      }
      else if(current.sprite_flipping == VERTICAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(1, -1));
      }
      else if(current.sprite_flipping == VERTICAL_AND_HORIZONTAL_FLIPPING)
      {
        transformed_sprite = sprite->transformed(QTransform().scale(-1, -1));
      }
      else
      {
        transformed_sprite = QImage(*sprite);
      }

      for(int m(0); m < m_global_data->sprite_height; ++m)
      {
        for(int n(0); n < m_global_data->sprite_width; ++n)
        {
          int editor_grid_row = (m_global_data->sprite_height+m_global_data->grid_heigth)*i + m;
          int editor_grid_column = (m_global_data->sprite_width+m_global_data->grid_width)*j + n;

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

  int palette_grid_height = color_height*colors_per_row + colors_per_row*m_global_data->grid_heigth;
  int palette_grid_width = color_width * colors_per_column +
      colors_per_column * m_global_data->grid_width;

  QImage palette_grid = QImage(palette_grid_width, palette_grid_height, QImage::Format_Indexed8);
  palette_grid.setColorTable(palette);
  QColor neutral_without_alpha(palette_grid.color(0));
  neutral_without_alpha.setRgb(neutral_without_alpha.rgb());

  palette_grid.setColor(0, neutral_without_alpha.rgb()); // Tirando o canal alpha da primeira cor
  palette_grid.setColorCount(palette_grid.colorCount()+1); // criando uma cor nova, por default e
  // transparente
  palette_grid.fill(palette_grid.colorCount()-1);

  for(int i(0); i < palette.size(); ++i)
  {
    for(int m(0); m < color_height; ++m)
    {
      for(int n(0); n < color_width; ++n)
      {
        int palette_grid_row = (color_height+m_global_data->grid_heigth)*row + n;
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
  const QVector<QImage *> &sprites = m_background->get_sprites();

  if(m_selected_sprite == -1)
    m_selected_sprite = sprites.size()-1;

  int pixel_width = m_selected_sprite_view->width() / m_global_data->sprite_width;
  int pixel_height = m_selected_sprite_view->height() / m_global_data->sprite_height;

  int pixel_size = pixel_width;
  if(pixel_height < pixel_size)
    pixel_size = pixel_height;

  QImage selected_sprite = QImage(pixel_size*m_global_data->sprite_width,
                                  pixel_size*m_global_data->sprite_height,
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

void cViewController::sprites_view_clicked(int x, int y)
{


  //std::ostringstream outs;
  //outs << e->pos().x() << "," << e->pos().y() << std::endl;
  //outs << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;
  //log->log(__LINE__, outs);

  //QGraphicsItem *i = scene()->itemAt(e->pos());
  //QGraphicsPixmapItem *p;

  //if ( QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(i) )
  //{
  //  scene()->removeItem(r);
  //  return;
  //}

  //if ( !(p = dynamic_cast<QGraphicsPixmapItem*>(i)) )
  //  return;

  //QImage t = p->pixmap().toImage();

  //int selSpriteX, selSpriteY;
  //selSpriteX = e->pos().x() / (sprite_width+imgData->sprite_grid_width);
  //selSpriteY = e->pos().y() / (sprite_height+imgData->sprite_grid_height);

  //int sel = (selSpriteY*sprites_per_line + selSpriteX);

  //if ( imgData->sprites.size() <= sel )
  //{
  //  return;
  //  if ( imgData->selectedSprite.x() >= 0 )
  //  {
  //    QGraphicsItem *i = scene()->itemAt(imgData->selectedSprite);

  //    if ( QGraphicsRectItem *r = dynamic_cast<QGraphicsRectItem *>(i) )
  //    {
  //      scene()->removeItem(r);
  //    }
  //  }

  //  QImage selSprite = QImage(sprite_width,sprite_height,t.format());
  //  {
  //    int spriteI, spriteJ;
  //    spriteI = e->pos().y() / (sprite_height+imgData->sprite_grid_height);
  //    spriteJ = e->pos().x() / (sprite_width+imgData->sprite_grid_width);
  //    for ( int i = 0 ; i < sprite_height ; i++ )
  //    {
  //      for ( int j = 0 ; j < sprite_width ; j++ )
  //      {
  //        selSprite.setPixel(j, i, t.pixel(j+spriteJ*(sprite_width+imgData->sprite_grid_width),
  //                                         i+spriteI*(sprite_height+imgData->sprite_grid_height)));
  //      }
  //    }
  //  }
  //  imgData->setSelectedSprite(selSprite);


  //  imgData->selectedSprite.setX(selSpriteX*(sprite_width+imgData->sprite_grid_width));
  //  imgData->selectedSprite.setY(selSpriteY*(sprite_height+imgData->sprite_grid_height));
  //  imgData->selectedSpriteId = (imgData->selectedSprite.y()*sprites_per_line + imgData->selectedSprite.x())/(sprite_width+imgData->sprite_grid_width);
  //  outs << "Selected id: " << imgData->selectedSpriteId << std::endl;
  //  log->log(__LINE__, outs);
  //  QPen l;
  //  l.setColor(Qt::yellow);
  //  l.setWidth(2);
  //  scene()->addRect(selSpriteX*(sprite_width+imgData->sprite_grid_width)-1,
  //                   selSpriteY*(sprite_height+imgData->sprite_grid_height)-1,
  //                   (sprite_width+imgData->sprite_grid_width),
  //                   (sprite_height+imgData->sprite_grid_height), l);

}

void cViewController::editor_view_clicked(int x, int y)
{
  QGraphicsScene *scene = m_editor_view->scene();
  if ( !scene )
    return;

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

  //    if ( btPaintPressed )
  //    {
  //        QPoint p = e->pos();

  //        std::ostringstream outs;
  //        outs << p.x() << "," << p.y() << std::endl;
  //        outs << "Left? "<< (e->buttons()&Qt::LeftButton) << " Right? " << (e->buttons()&Qt::RightButton) << std::endl;
  //        log.log(__LINE__, outs);

  //        QList<QGraphicsItem *> items = scene()->items();
  //        QList<QGraphicsItem *>::iterator it;
  //        QGraphicsPixmapItem *pi;

  //        it = items.begin();
  //        while ( !(pi = dynamic_cast<QGraphicsPixmapItem*>(*it)) && it != items.end() )
  //        {
  //            it++;
  //        }
  //	if ( it == items.end() ) return;
  //	// Encontramos assim o Pixmap que está sendo usado no VisualizationGrid

  //        p.setX(p.x()+horizontalScrollBar()->value());
  //        p.setX(p.x()/(sprite_width+imgData->visualization_grid_width));
  //        p.setY(p.y()/(sprite_height+imgData->visualization_grid_height));

  //	outs << "Sprite: " << p.x() << "," << p.y() << std::endl;
  //        log.log(__LINE__,outs);

  //        if ( imgData->selectedSprite.x() >= 0 )
  //        {
  //            QPixmap gridPix = pi->pixmap();

  //            QPoint spritePt = imgData->selectedSprite;

  //	    QBitmap bitMask = QBitmap(gridPix.mask());
  //	    QPainter painter;


  //	    int mySpriteIndex;
  //	    mySpriteIndex = (spritePt.y() / (sprite_height+imgData->sprite_grid_height));
  //	    mySpriteIndex *= (imgData->spriteGrid.width()+1) / (sprite_width+imgData->sprite_grid_width);
  //	    mySpriteIndex += (spritePt.x() / (sprite_width+imgData->sprite_grid_width));
  //	    // Simplemente o índice do sprite que foi selecionado. Desse modo, podemos facilmente
  //	    // acessar os sprites no vetor. Sprites esses que já estão indexados pela paletta.
  //	    // Ou seja, basta usarmos o índice na hora de usá-los.

  //	    painter.begin(&bitMask);
  //	    for ( int i = 0 ; i < sprite_height ; i++ )
  //            {
  //                for ( int j = 0 ; j < sprite_width ; j++ )
  //                {
  //		    int cIndex = imgData->sprites[mySpriteIndex].pixelIndex(j,i);
  //		    QColor srcColor = QColor::fromRgba(imgData->nPalette[cIndex]);

  //		    int x;
  //		    int y;

  //		    x = j+p.x()*(sprite_width+imgData->visualization_grid_width);
  //		    y = i+p.y()*(sprite_height+imgData->visualization_grid_height);
  //		    // Aqui nós desenhamos o alpha mask do visualizationGrid.
  //		    // Caso a cor tenha alpha, ela é desenhado como transparente,
  //		    // pois no DS só há um bit de transparência.
  //		    if ( srcColor.alpha() != 255 )
  //		    {
  //			painter.setPen(Qt::color0);
  //			painter.drawPoint(x, y);
  //		    }
  //		    else
  //		    {
  //			painter.setPen(Qt::color1);
  //			painter.drawPoint(x, y);
  //		    }
  //		    imgData->visualizationGrid.setPixel(x, y, cIndex);
  //                }
  //            }
  //	    painter.end();

  //	    gridPix = gridPix.fromImage(imgData->visualizationGrid);
  //	    gridPix.setMask(bitMask);
  //            pi->setPixmap(gridPix);

  //            imgData->bgmatrix[p.y()][p.x()] = imgData->selectedSpriteId;
  //	} // end if ( imgData->selectedSprite.x() >= 0 )
  //    } // end if ( btPaintPressed )
  //    else
  //    {
  //	// Somente para testar o efeito de mudar uma cor num objeto com formato 8-bit indexed.
  //	// Apagar depois dos testes!
  //	QList<QGraphicsItem *> items = scene()->items();
  //	QList<QGraphicsItem *>::iterator it;
  //	QGraphicsPixmapItem *pi;

  //	it = items.begin();
  //	while ( !(pi = dynamic_cast<QGraphicsPixmapItem*>(*it)) && it != items.end() )
  //	{
  //	    it++;
  //	}
  //	if ( it == items.end() ) return;

  //	QPixmap gridPix ;
  //	QColor q = Qt::darkMagenta;
  //	imgData->visualizationGrid.setColor(2,q.rgba());
  //	gridPix = gridPix.fromImage(imgData->visualizationGrid);
  //	pi->setPixmap(gridPix);

  //    }

}
