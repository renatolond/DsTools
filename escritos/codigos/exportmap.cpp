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
