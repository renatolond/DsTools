#include "level-data.h"

#include "object-controller.h"

void sLevelData::insert_into_list(cObjectController *object)
{
  std::list<cObjectController *>::iterator it;


  for(it = m_objects.begin(); it != m_objects.end(); ++it)
  {
    cObjectController *inserted = *it;
    if(inserted->get_center() > object->get_center())
    {
      m_objects.insert(it, object);
      return;
    }
  }

  m_objects.push_back(object);
}

std::list<cObjectController *>& sLevelData::get_objects(void)
{
  return m_objects;
}
