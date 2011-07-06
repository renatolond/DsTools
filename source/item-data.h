#ifndef ITEMDATA_H
#define ITEMDATA_H

enum eItemType
{
  ITEMBOX
};

struct sItemData
{
  int m_x, m_y, m_h, m_w;
  const void *m_sprite_pointer;
  const void *m_palette_pointer;
  eItemType m_item_type;
  void set_size(int h, int w);
};

#endif // ITEMDATA_H
