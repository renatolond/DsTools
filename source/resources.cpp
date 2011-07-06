#include <vector>

#include <PA9.h>

#include "enemy-data.h"
#include "item-data.h"
#include "level-data.h"

#include "all_gfx.h"

// TODO(renatolond, 2011-06-23) Remove this as constant, put it elsewhere.
extern const int multiplier;

//extern const unsigned char goomba_Sprite[3328] _GFX_ALIGN;
//extern const unsigned char itembox_Sprite[3328] _GFX_ALIGN;
//extern const unsigned short goomba_Pal[256] _GFX_ALIGN;
//extern const unsigned short itembox_Pal[256] _GFX_ALIGN;

extern const PA_BgStruct level1_0;

void load_level1(std::vector<sLevelData *>& level_data_vector)
{
  sLevelData *level1_data = new sLevelData();
  level1_data->m_world_min_height = 0;
  level1_data->m_world_min_width = 0;
  level1_data->m_world_max_height = SuperMarioClone0.height*multiplier;
  level1_data->m_world_max_width = SuperMarioClone0.width*multiplier;
  level1_data->m_scrolled = 0;
  level1_data->m_backgrounds.push_back(&SuperMarioClone0);

//  sItemData *itembox1 = new sItemData();
//  itembox1->m_x = 30;
//  itembox1->m_y = 9;
//  itembox1->m_sprite_pointer = itembox_Sprite;
//  itembox1->m_palette_pointer = itembox_Pal;
//  itembox1->set_size(OBJ_SIZE_16X16);
//  itembox1->m_item_type = ITEMBOX;

//  level1_data->m_items.push_back(itembox1);

//  sEnemyData *goomba1 = new sEnemyData();
//  goomba1->m_x = 30;
//  goomba1->m_y = 3;
//  goomba1->m_sprite_pointer = goomba_Sprite;
//  goomba1->m_palette_pointer = goomba_Pal;
//  goomba1->set_size(OBJ_SIZE_16X16);
//  goomba1->m_enemy_movement = STRAIGHT_FALL;

//  level1_data->m_enemies.push_back(goomba1);

  level_data_vector.push_back(level1_data);
}

void load_resources(std::vector<sLevelData *>& level_data_vector)
{
  // Here you put all things you want to get loaded into scroll engine.
  load_level1(level_data_vector);
}
