struct sLevelData
{
  std::vector<const PA_BgStruct *> m_backgrounds;
  std::vector<sEnemyData *> m_enemies;
  std::vector<sItemData *> m_items;
  int m_scrolled;
  int m_world_min_height;
  int m_world_min_width;
  int m_world_max_height;
  int m_world_max_width;
};
  