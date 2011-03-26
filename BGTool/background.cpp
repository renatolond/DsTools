#include "background.h"

#include <QColor>
#include <QDataStream>
#include <QFile>
#include <QImage>
#include <QPixmap>
#include <QTextStream>

#include "globaldata.h"


cBackground::cBackground(QString name, sGlobalData *global_data):
                        m_name(name),
                        m_global_data(global_data)
{
}


void cBackground::insert_into_palette(QColor c)
{
  m_palette.push_back(c.rgba());
}

QRgb toR5G5B5A1(QColor c, QColor *neutral)
{
  if(c.alpha() != 255)
    return neutral->rgba();

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
  m_neutral = new QColor();
  m_neutral->setAlpha(0); // 0 significa que a cor não é visível
  m_neutral->setRed(m_global_data->neutral_red);
  m_neutral->setGreen(m_global_data->neutral_green);
  m_neutral->setBlue(m_global_data->neutral_blue);
  insert_into_palette(*m_neutral);
  QColor c;
  c.setRgba(toR5G5B5A1(*m_neutral, m_neutral));
  m_color_hash[m_neutral->rgba()] = 0;

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

void cBackground::find_sprites(QImage &image)
{

  QImage *empty_sprite = new QImage(m_global_data->sprite_width, m_global_data->sprite_height,
                      QImage::Format_Indexed8);
  empty_sprite->setColorTable(m_palette);
  empty_sprite->fill(0); // Primeiro índice da tabela de cores é sempre a cor neutra, transparente

  for(int i(0); i < (image.height() / m_global_data->sprite_height) ; ++i)
  {
    for(int j(0); j < (image.width() / m_global_data->sprite_width) ; ++j)
    {
      QImage *sprite = new QImage(m_global_data->sprite_width, m_global_data->sprite_height,
                                  QImage::Format_Indexed8);
      sprite->setColorTable(m_palette);
      for(int k(0); k < m_global_data->sprite_height ; ++k)
      {
        for(int l(0); l < m_global_data->sprite_width ; ++l)
        {
          int height_index = i*m_global_data->sprite_height + k;
          int width_index = j*m_global_data->sprite_width + l;
          QColor c;
          c.setRgba(toR5G5B5A1(image.pixel(width_index, height_index), m_neutral));
          sprite->setPixel(l, k, m_color_hash[c.rgba()]);
        }
      }
      eSpriteFlipping sprite_flipping;
      int sprite_index = insert_into_sprites(sprite, sprite_flipping);
      push_back_map_matrix(i, sprite_index, sprite_flipping);
    }
  }

  m_sprites.push_back(empty_sprite);
}

int cBackground::insert_into_sprites(QImage *sprite, eSpriteFlipping &sprite_flipping)
{
  return 0;
}

void cBackground::push_back_map_matrix(int y, int sprite_index, eSpriteFlipping sprite_flipping)
{
  sSpriteInfo sprite_info;
  sprite_info.sprite_index = sprite_index;
  m_map_matrix[y].push_back(sprite_index);
}

void cBackground::import_image(QString path)
{
  QImage image(path);
  find_palette(image);
  find_sprites(image);
}

void cBackground::export_to_ds()
{
  QString pal, tiles, map, cfile;
  //std::string pal, tiles, map, cfile;
  pal = "../gfx/bin/" + m_name  + "_Pal.bin";
  tiles = "../gfx/bin/" + m_name + "_Tiles.bin";
  map = "../gfx/bin/" + m_name + "_Map.bin";
  cfile = "../gfx/bin/" + m_name + ".c";

  // exporting palette7
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

      //unsigned char red, blue;
      //red = c->red(); green = c->green(); blue = c->blue();

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
  //  sout = fopen(tiles.c_str(), "wb");
  //  for ( QVector<QImage *>::iterator it = m_sprites.begin() ; it != m_sprites.end() ; it++ )
  //  {
  //    QImage *pt = *it;
  //    for ( int i = 0 ; i < 8 ; i++ )
  //    {
  //      for ( int j = 0 ; j < 8 ; j++ )
  //      {
  //        unsigned char k = pt->pixelIndex(j,i);
  //        fwrite(&k, 1, sizeof(k), sout);
  //      }
  //    }
  //  }

  //  for ( int i = 0 ; i < 64 ; i++ )
  //  {
  //    unsigned char k = 0;
  //    fwrite(&k,1,sizeof(k),sout);
  //  }
  //  fclose(sout);

  //  //exporting map
  //  sout = fopen(map.c_str(), "wb");
  //  for ( int i = 0 ; i < m_map_matrix.size() ; i++ )
  //  {
  //    for ( int j = 0 ; j < m_map_matrix[i].size() ; j++ )
  //    {
  // TODO(lond, 2011-03-23) Fazer um map dos ponteiros apontando para os sprites
  //      //unsigned char k = m_map_matrix[i][j];
  //      unsigned char k;
  //      unsigned char zero = 0;
  //      fwrite(&k,1,sizeof(k),sout);
  //      fwrite(&zero, 1, sizeof(zero), sout);
  //    }
  //  }
  //  fclose(sout);

  QFile file_cfile(cfile);
  if(file_cfile.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QTextStream out(&file_cfile);

    int map_matrix_height = m_map_matrix.size();
    int map_matrix_width = m_map_matrix[0].size();

    out << "#include <PA_BgStruct.h>" << endl;
    out << endl;
    out << "extern const char bgtool" << m_name << "_Tiles[];" << endl;
    out << "extern const char bgtool" << m_name << "_Map[];" << endl;
    out << "extern const char bgtool" << m_name << "_Pal[];" << endl;
    out << endl;
    out << "const PA_BgStruct bgtool" << m_name << " = {" << endl;
    out << "  PA_BgLarge," << endl;
    out << "  " << map_matrix_width*8 << ", " << map_matrix_height*8 << "," << endl;
    out << endl;
    out << "bgtool" << m_name << "_Tiles," << endl;
    out << "bgtool" << m_name << "_Map," << endl;
    out << "{bgtool" << m_name << "_Pal}," << endl;
    out << endl;
    out << m_sprites.size()*8*8 << "," << endl;
    out << "{" << map_matrix_height*map_matrix_width*2 << "}" << endl;
    out << "};" << endl;
  }
  file_cfile.close();
}
