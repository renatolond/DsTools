void load_level1(std::vector<sLevelData *>& level_data_vector)
{
  sLevelData *level1_data = new sLevelData();
  level1_data->m_world_min_height = 0;
  level1_data->m_world_min_width = 0;
  level1_data->m_world_max_height = level1_0.height*multiplier;
  level1_data->m_world_max_width = level1_0.width*multiplier;
  level1_data->m_scrolled = 0;
  level1_data->m_backgrounds.push_back(&level1_0);

  sItemData *itembox1 = new sItemData();
  itembox1->m_x = 30;
  itembox1->m_y = 9;
  itembox1->m_sprite_pointer = itembox_Sprite;
  itembox1->m_palette_pointer = itembox_Pal;
  itembox1->set_size(OBJ_SIZE_16X16);
  itembox1->m_item_type = ITEMBOX;

  level1_data->m_items.push_back(itembox1);
  
  (... Outros itens inseridos do mesmo modo ...)

  sEnemyData *goomba1 = new sEnemyData();
  goomba1->m_x = 30;
  goomba1->m_y = 3;
  goomba1->m_sprite_pointer = goomba_Sprite;
  goomba1->m_palette_pointer = goomba_Pal;
  goomba1->set_size(OBJ_SIZE_16X16);
  goomba1->m_enemy_movement = STRAIGHT_FALL;

  level1_data->m_enemies.push_back(goomba1);
  
  (... Outros inimigos inseridos do mesmo modo ...)

  level_data_vector.push_back(level1_data);
}
