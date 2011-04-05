#include "project.h"

#include "level.h"

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

void cProject::delete_active_level(void)
{
  int i(0);
  for(; i < m_levels.size(); ++i)
    if(m_levels[i] == m_active_level)
      break;

  m_levels.erase(m_levels.begin()+i);

  delete m_active_level;

  if(m_levels.size() > 0)
    m_active_level = m_levels[0];
  else
    m_active_level = NULL;
}
