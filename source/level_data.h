#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <vector>

#include "PA_BgStruct.h" // No way to do forward declaration, apparently

class sObject;

class sLevelData
{
protected:
public:
  std::vector<const PA_BgStruct *> m_backgrounds;
  std::vector<void *> m_palettes;
  void *m_player_sprite;
  int m_player_palette_index;
  int m_player_start_x;
  int m_player_start_y;
  std::vector<sObject *> m_objects;

  sLevelData();
};

#endif // LEVEL_DATA_H
