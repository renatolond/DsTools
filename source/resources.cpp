#include <vector>

#include <PA9.h>

#include "item-box.h"
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

  level1_data->m_palettes.push_back(ItemBox_Pal);

  cItemBox *itembox1 = new cItemBox(33*8, 13*8);
  itembox1->m_sprite_pointer = ItemBox_Sprite;
  itembox1->m_palette_index = 0;
  itembox1->set_size(OBJ_SIZE_16X16);


  cItemBox *itembox2 = new cItemBox(43*8, 13*8);
  itembox2->m_sprite_pointer = ItemBox_Sprite;
  itembox2->m_palette_index = 0;
  itembox2->set_size(OBJ_SIZE_16X16);


  cItemBox *itembox3 = new cItemBox(47*8, 13*8);
  itembox3->m_sprite_pointer = ItemBox_Sprite;
  itembox3->m_palette_index = 0;
  itembox3->set_size(OBJ_SIZE_16X16);


  cItemBox *itembox4 = new cItemBox(45*8, 5*8);
  itembox4->m_sprite_pointer = ItemBox_Sprite;
  itembox4->m_palette_index = 0;
  itembox4->set_size(OBJ_SIZE_16X16);

  cItemBox *itembox5 = new cItemBox(33*8, 0);
  itembox5->m_sprite_pointer = ItemBox_Sprite;
  itembox5->m_palette_index = 0;
  itembox5->set_size(OBJ_SIZE_16X16);

  level1_data->insert_into_list(itembox1);
  level1_data->insert_into_list(itembox2);
  level1_data->insert_into_list(itembox3);
  level1_data->insert_into_list(itembox4);
  level1_data->insert_into_list(itembox5);

  //level1_data->m_items.push_back(itembox1);

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
