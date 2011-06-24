#include <vector>

#include "level-data.h"

#include "all_gfx.h"

// TODO(renatolond, 2011-06-23) Remove this as constant, put it elsewhere.
extern const int multiplier;

void load_level1(std::vector<sLevelData *>& level_data_vector)
{
  sLevelData *level1_data = new sLevelData();
  level1_data->m_world_min_height = 0;
  level1_data->m_world_min_width = 0;
  level1_data->m_world_max_height = bgtool0.height*multiplier;
  level1_data->m_world_max_width = bgtool0.width*multiplier;
  level1_data->m_scrolled = 0;
  level1_data->m_backgrounds.push_back(&bgtool0);
  level_data_vector.push_back(level1_data);
}

void load_resources(std::vector<sLevelData *>& level_data_vector)
{
  // Here you put all things you want to get loaded into scroll engine.
  load_level1(level_data_vector);
}
