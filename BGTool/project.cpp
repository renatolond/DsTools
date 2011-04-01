#include "project.h"

cProject::cProject()
{
}

cLevel* cProject::active_level(void)
{
  return m_active_level;
}

void cProject::new_level(cLevel *level)
{
  m_levels.push_back(level);
  m_active_level = level;
}
