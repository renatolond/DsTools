#include "level.h"

#include "background.h"

cLevel::cLevel()
{
}

int cLevel::num_layers(void)
{
  return m_backgrounds.size();
}

cBackground* cLevel::get_background(int n)
{
  if(n >= m_backgrounds.size())
    return NULL;
  return m_backgrounds[n];
}

cLevel::cLevel(QString name, int num_layers, int size_x, int size_y, sGlobalData *global_data):
  m_name(name),
  m_size_x(size_x),
  m_size_y(size_y)
{
  for(int i(0); i < num_layers; ++i)
  {
    cBackground *bg = new cBackground(name+QString::number(i), size_x, size_y, global_data);
    m_backgrounds.push_back(bg);
  }
}
