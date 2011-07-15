#include "resources.h"

#include "all_gfx.h"

#include "level_data.h"
#include "object.h"

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void load_level1(std::vector<sLevelData *>& level_data_vector)
{
  sLevelData *level1_data = new sLevelData();
  level1_data->m_backgrounds.push_back(&SuperMarioClone0);

  level1_data->m_palettes.push_back((void*)SuperMarioClone_Pal);
  level1_data->m_palettes.push_back((void*)ItemBox_Pal);

  level1_data->m_player_sprite = (void*)SuperMarioClone_Sprite;
  level1_data->m_player_palette_index = 0;
  level1_data->m_player_start_x = 0;
  level1_data->m_player_start_y = 0;

  sObject *itembox = new sObject();
  itembox->m_sprite = (void*)ItemBox_Sprite;
  itembox->m_palette_index = 1;
  itembox->m_x = 32*8;
  itembox->m_y = 13*8;

  level1_data->m_objects.push_back(itembox);

  itembox = new sObject();
  itembox->m_sprite = (void*)ItemBox_Sprite;
  itembox->m_palette_index = 1;
  itembox->m_x = 42*8;
  itembox->m_y = 13*8;

  level1_data->m_objects.push_back(itembox);

  itembox = new sObject();
  itembox->m_sprite = (void*)ItemBox_Sprite;
  itembox->m_palette_index = 1;
  itembox->m_x = 46*8;
  itembox->m_y = 13*8;

  level1_data->m_objects.push_back(itembox);

  itembox = new sObject();
  itembox->m_sprite = (void*)ItemBox_Sprite;
  itembox->m_palette_index = 1;
  itembox->m_x = 44*8;
  itembox->m_y = 5*8;

  level1_data->m_objects.push_back(itembox);

  itembox = new sObject();
  itembox->m_sprite = (void*)ItemBox_Sprite;
  itembox->m_palette_index = 1;
  itembox->m_x = 0;
  itembox->m_y = 0;

  level1_data->m_objects.push_back(itembox);

  level_data_vector.push_back(level1_data);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void load_resources(std::vector<sLevelData *>& level_data_vector)
{
  // Here you put all things you want to get loaded into scroll engine.
  load_level1(level_data_vector);
}
