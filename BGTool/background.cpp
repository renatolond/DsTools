#include "background.h"

#include <QColor>
#include <QDataStream>
#include <QDomDocument>
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QTextStream>

#include "globaldata.h"


cBackground::cBackground(QDomElement &background_node, sGlobalData *global_data, QString path)
{
  m_global_data = global_data;

  QString name = background_node.attribute("Name");
  m_name = name;

  QString tiles_path = background_node.attribute("Tile_Set");

  QImage image(path + tiles_path);
  find_palette(image);
  find_tile(image);

  clear_map();

  QString map_path = background_node.attribute("Path");
  QImage map_image(path + map_path);
  find_tile(map_image);
}

cBackground::cBackground(QString name, int size_x, int size_y, sGlobalData *global_data):
                        m_name(name),
                        m_global_data(global_data)
{
  QImage empty_image = QImage(size_x, size_y, QImage::Format_Indexed8);
  QColor c = QColor(m_global_data->neutral_red, m_global_data->neutral_green,
                    m_global_data->neutral_red, 0);
  empty_image.setColor(0, c.rgb());
  empty_image.fill(0);
  find_palette(empty_image);
  find_tile(empty_image);
}


void cBackground::insert_into_palette(QColor c)
{
  m_palette.push_back(c.rgba());
}

QRgb toR5G5B5A1(QColor c, QColor *neutral)
{
  if(c.alpha() != 255)
  {
    c = *neutral;
    c.setAlpha(255);
  }

  unsigned int color;
  color = c.red();
  color = color >> 3;
  color = color << 3;
  c.setRed(color);

  color = c.green();
  color = color >> 3;
  color = color << 3;
  c.setGreen(color);

  color = c.blue();
  color = color >> 3;
  color = color << 3;
  c.setBlue(color);

  return c.rgba();
}

void cBackground::find_palette(QImage &image)
{
  m_neutral = new QColor(Qt::magenta);
  m_neutral->setAlpha(0); // 0 significa que a cor não é visível
  m_neutral->setRed(m_global_data->neutral_red);
  m_neutral->setGreen(m_global_data->neutral_green);
  m_neutral->setBlue(m_global_data->neutral_blue);
  insert_into_palette(*m_neutral);
  QColor c;
  c.setRgba(toR5G5B5A1(*m_neutral, m_neutral));
  m_color_hash[c.rgba()] = 0;

  for(int i(0); i < image.height(); i++)
  {
    for(int j(0); j < image.width(); j++)
    {
      c.setRgba(toR5G5B5A1(image.pixel(j, i), m_neutral));
      if(!m_color_hash.contains(c.rgba()))
      {
        m_color_hash[c.rgba()] = m_palette.size();
        insert_into_palette(c);
      }
    }
  }
}

void cBackground::find_tile(QImage &image)
{
  QImage *empty_tile = new QImage(m_global_data->tile_width, m_global_data->tile_height,
                      QImage::Format_Indexed8);
  empty_tile->setColorTable(m_palette);
  empty_tile->fill(0); // Primeiro índice da tabela de cores é sempre a cor neutra, transparente

  for(int i(0); i < (image.height() / m_global_data->tile_height) ; ++i)
  {
    for(int j(0); j < (image.width() / m_global_data->tile_width) ; ++j)
    {
      QImage *tile = new QImage(m_global_data->tile_width, m_global_data->tile_height,
                                  QImage::Format_Indexed8);
      tile->setColorTable(m_palette);
      for(int k(0); k < m_global_data->tile_height ; ++k)
      {
        for(int l(0); l < m_global_data->tile_width ; ++l)
        {
          int height_index = i*m_global_data->tile_height + k;
          int width_index = j*m_global_data->tile_width + l;
          QColor c;
          c.setRgba(toR5G5B5A1(image.pixel(width_index, height_index), m_neutral));
          tile->setPixel(l, k, m_color_hash[c.rgba()]);
        }
      }
      eTileFlipping tile_flipping;
      int tile_index = insert_into_tiles(tile, tile_flipping);
      push_back_map_matrix(i, tile_index, tile_flipping);
    }
  }

  sTileInfo tile_info;
  tile_info.m_tile = empty_tile;
  tile_info.m_tile_collision = COLLISION_EMPTY;
  m_tile_collision.push_back(tile_info);
}

int cBackground::insert_into_tiles(QImage *tile, eTileFlipping &tile_flipping)
{
  QImage HFlip, VFlip, VHFlip;

  HFlip  = tile->transformed(QTransform().scale(-1,  1));
  VFlip  = tile->transformed(QTransform().scale( 1, -1));
  VHFlip = tile->transformed(QTransform().scale(-1, -1));

  for(int i(0); i < m_tile_collision.size(); i++)
  {
    sTileInfo tile_info = m_tile_collision[i];
    if((*tile) == (*(tile_info.m_tile)))
    {
      tile_flipping = NO_FLIPPING;
      return i;
    }
    if(HFlip == (*(tile_info.m_tile)))
    {
      tile_flipping = HORIZONTAL_FLIPPING;
      return i;
    }
    if(VFlip == (*(tile_info.m_tile)))
    {
      tile_flipping = VERTICAL_FLIPPING;
      return i;
    }
    if(VHFlip == (*(tile_info.m_tile)))
    {
      tile_flipping = VERTICAL_AND_HORIZONTAL_FLIPPING;
      return i;
    }
  }

  int index = m_tile_collision.size();
  sTileInfo tile_info;
  tile_info.m_tile = tile;
  tile_info.m_tile_collision = COLLISION_EMPTY;
  m_tile_collision.push_back(tile_info);
  tile_flipping = NO_FLIPPING;

  return index;
}

void cBackground::push_back_map_matrix(int y, int tile_index, eTileFlipping tile_flipping)
{
  if(m_map_matrix.size() == y)
    m_map_matrix.push_back(QVector<sMapInfo>());
  sMapInfo map_info;
  map_info.m_tile_index = tile_index;
  map_info.m_tile_flipping = tile_flipping;
  m_map_matrix[y].push_back(map_info);
}

void cBackground::clear_map(void)
{
  int size = m_map_matrix.size();
  for(int i(0); i < size; ++i)
  {
    m_map_matrix[i].clear();
  }
  m_map_matrix.clear();
}

void cBackground::clear_background(void)
{
  int size = m_tile_collision.size();
  for(int i(0); i < size; ++i)
  {
    sTileInfo tile_info = m_tile_collision.last();
    delete tile_info.m_tile;
    m_tile_collision.pop_back();
  }

  m_palette.clear();
  m_color_hash.clear();

  clear_map();
}

void cBackground::import_image(QString path)
{
  clear_background();
  QImage image(path);
  find_palette(image);
  find_tile(image);
}

void cBackground::export_map_to_ds()
{
  QString map = "../gfx/bin/" + m_name + "_Map.bin";

  //exporting map
  QFile file_map(map);
  if(file_map.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_map);
    for(int i(0); i < m_map_matrix.size(); ++i)
    {
      for(int j(0); j < m_map_matrix[i].size(); ++j)
      {
        unsigned char tile_index;
        unsigned char tile_flipping;
        sMapInfo tile = m_map_matrix[i][j];
        tile_index = (unsigned char) tile.m_tile_index;
        tile_flipping = ((tile.m_tile_index & (1024+512)) >> 8);
        if(tile.m_tile_flipping == VERTICAL_AND_HORIZONTAL_FLIPPING)
        {
          tile_flipping |= 4 + 8; // bit 3 e 4
        }
        if(tile.m_tile_flipping == HORIZONTAL_FLIPPING)
        {
          tile_flipping |= 4;
        }
        if(tile.m_tile_flipping == VERTICAL_FLIPPING)
        {
          tile_flipping |= 8;
        }
        out.writeRawData((const char *)&tile_index, 1);
        out.writeRawData((const char *)&tile_flipping, 1);
      }
    }
  }
  file_map.close();
}

void cBackground::export_to_ds()
{
  QString pal, tiles, cfile;
  //std::string pal, tiles, map, cfile;
  pal = "../gfx/bin/" + m_name  + "_Pal.bin";
  tiles = "../gfx/bin/" + m_name + "_Tiles.bin";
  cfile = "../gfx/bin/" + m_name + ".c";

  // exporting palette
  QFile file_pal(pal);
  if(file_pal.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_pal);
    for ( int i = 0 ; i < m_palette.size() ; i++ )
    {
      QColor c;
      c = m_palette[i];

      unsigned char high, low;
      high = 1;
      high = high << 5;
      high += ( c.blue() >> 3 );
      high = high << 2;
      high += ( c.green() >> 6 );

      unsigned char green = c.green() - ((c.green() >> 6)<<6);
      low = (green >> 3);
      low = low << 5;
      low += ( c.red() >> 3);

      out.writeRawData((const char *)&low, 1);
      out.writeRawData((const char *)&high, 1);
    }
    for ( int i = m_palette.size() ; i < 256 ; i++ )
    {
      unsigned char zero;
      zero = 0;
      out.writeRawData((const char *)&zero, 1);
      out.writeRawData((const char *)&zero, 1);
    }
  }
  file_pal.close();

  //exporting tiles
  QFile file_tiles(tiles);
  if(file_tiles.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_tiles);
    for(QVector<sTileInfo>::iterator it = m_tile_collision.begin(); it != m_tile_collision.end(); ++it)
    {
      QImage *pt = it->m_tile;
      for(int i(0); i < m_global_data->tile_height; ++i)
      {
        for(int j(0); j < m_global_data->tile_width; ++j)
        {
          unsigned char color_index = pt->pixelIndex(j, i);
          out.writeRawData((const char *)&color_index, 1);
        }
      }
    }
  }
  file_tiles.close();

  export_map_to_ds();

  QFile file_cfile(cfile);
  if(file_cfile.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QTextStream out(&file_cfile);

    int map_matrix_height = m_map_matrix.size();
    int map_matrix_width = m_map_matrix[0].size();

    out << "#include <PA_BgStruct.h>" << endl;
    out << endl;
    out << "extern const char " << m_name << "_Tiles[];" << endl;
    out << "extern const char " << m_name << "_Map[];" << endl;
    out << "extern const char " << m_name << "_Pal[];" << endl;
    out << endl;
    out << "const PA_BgStruct " << m_name << " = {" << endl;
    out << "  PA_BgLarge," << endl;
    out << "  " << map_matrix_width*8 << ", " << map_matrix_height*8 << "," << endl;
    out << endl;
    out << "" << m_name << "_Tiles," << endl;
    out << "" << m_name << "_Map," << endl;
    out << "{" << m_name << "_Pal}," << endl;
    out << endl;
    out << m_tile_collision.size()*8*8 << "," << endl;
    out << "{" << map_matrix_height*map_matrix_width*2 << "}" << endl;
    out << "};" << endl;
  }
  file_cfile.close();
}

const QVector<QRgb>& cBackground::get_palette(void)
{
  return m_palette;
}

const QVector<sTileInfo>& cBackground::get_tiles(void)
{
  return m_tile_collision;
}

const QVector< QVector<sMapInfo> >& cBackground::get_map_matrix(void)
{
  return m_map_matrix;
}


void cBackground::set_map_matrix(int x, int y, int tile_index, eTileFlipping tile_flipping)
{
  sMapInfo map_info;
  map_info.m_tile_index = tile_index;
  map_info.m_tile_flipping = tile_flipping;

  m_map_matrix[y][x] = map_info;
}

void cBackground::export_to_xml(QDomDocument *xml_document, QDomElement *backgrounds_node,
                                QString path)
{
  QDomElement background_node = xml_document->createElement("Background");
  backgrounds_node->appendChild(background_node);
  background_node.setAttribute("Name", m_name);
  background_node.setAttribute("Path", m_name + ".png");
  background_node.setAttribute("Tile_Set", m_name + "_tiles.png");
  export_to_png(path + m_name + ".png");
  export_tiles_to_png(path + m_name + "_tiles.png");
}

void cBackground::export_to_png(QString path)
{
  QImage map(m_global_data->tile_width * m_map_matrix[0].size(),
             m_global_data->tile_height * m_map_matrix.size(),
             m_tile_collision[0].m_tile->format());
  map.setColorTable(m_palette);

  for(int i(0); i < m_map_matrix.size(); ++i)
  {
    for(int j(0); j < m_map_matrix[i].size(); ++j)
    {
      QImage tile;
      if(m_map_matrix[i][j].m_tile_flipping == NO_FLIPPING)
      {
        tile = m_tile_collision[m_map_matrix[i][j].m_tile_index].m_tile->transformed(
              QTransform().scale(1,  1));
      }
      else if(m_map_matrix[i][j].m_tile_flipping == HORIZONTAL_FLIPPING)
      {
        tile = m_tile_collision[m_map_matrix[i][j].m_tile_index].m_tile->transformed(
              QTransform().scale(-1,  1));
      }
      else if(m_map_matrix[i][j].m_tile_flipping == VERTICAL_FLIPPING)
      {
        tile = m_tile_collision[m_map_matrix[i][j].m_tile_index].m_tile->transformed(
              QTransform().scale(1,  -1));
      }
      else if(m_map_matrix[i][j].m_tile_flipping == VERTICAL_AND_HORIZONTAL_FLIPPING)
      {
        tile = m_tile_collision[m_map_matrix[i][j].m_tile_index].m_tile->transformed(
              QTransform().scale(-1,  -1));
      }
      for(int k(0); k < m_global_data->tile_width; ++k)
      {
        for(int l(0); l < m_global_data->tile_height; ++l)
        {
          map.setPixel(j*m_global_data->tile_width + k, i*m_global_data->tile_height + l,
                       tile.pixelIndex(k, l));
        }
      }
    }
  }

  if(!map.save(path))
  {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << "Erro ao salvar imagem " << path << endl;
  }
}

void cBackground::export_tiles_to_png(QString path)
{
  QImage tileset(m_global_data->tile_width * m_tile_collision.size(), m_global_data->tile_height,
                 m_tile_collision[0].m_tile->format());
  tileset.setColorTable(m_palette);

  for(int i(0); i < m_tile_collision.size(); ++i)
  {
    for(int j(0); j < m_global_data->tile_width; ++j)
    {
      for(int k(0); k < m_global_data->tile_height; ++k)
      {
        tileset.setPixel(i*m_global_data->tile_width + j, k,
                         m_tile_collision[i].m_tile->pixelIndex(j, k));
      }
    }
  }

  if(!tileset.save(path))
  {
    QTextStream cout(stdout, QIODevice::WriteOnly);
    cout << "Erro ao salvar imagem " << path << endl;
  }
}
