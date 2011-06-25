  //exporting sprite
  QFile file_spr(spr);

  if(file_spr.open(QIODevice::WriteOnly | QFile::Truncate))
  {
    QDataStream out(&file_spr);

    int paletteBias = 0;

    for(int it(0); it < m_sprite.size(); ++it)
    {
      QImage img = pImg.at(it);

      for(int i(0); i < m_sprite.get_height()/8; ++i)
      {
        for(int j(0); j < m_sprite.get_width()/8; ++j)
        {
          for(int ii(0); ii < 8; ++ii)
          {
            for(int jj(0); jj < 8; ++jj)
            {
              unsigned char color_index;

              if(img.pixelIndex(8*j+jj,8*i+ii) == 0)
                color_index = 0;
              else
                color_index = img.pixelIndex(8*j+jj,8*i+ii) + paletteBias;

              out.writeRawData((const char *)&color_index,1);
            }
          }
        }
      }

      paletteBias += img.colorTable().size();
    }
  }

  file_spr.close();