#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>
#include <list>

#include "PA_BgStruct.h" // No way to do forward declaration, apparently

class cObjectController;

struct sLevelData
{
protected:
  std::list<cObjectController *> m_objects;
public:
  std::vector<const PA_BgStruct *> m_backgrounds;
  //std::vector<cObjectController *> m_objects;

  void insert_into_list(cObjectController *object);
  std::list<cObjectController *>& get_objects(void);

  int m_scrolled;
  int m_world_min_height;
  int m_world_min_width;
  int m_world_max_height;
  int m_world_max_width;
};

#endif // LEVELDATA_H
