#include "object.h"

#include <PA9.h>

sObject::sObject()
{
  m_sprite_id = -1;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void sObject::move(int screen_scrolled)
{
  PA_SetSpriteXY(0, m_sprite_id, m_x-screen_scrolled, m_y);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool sObject::exists(void)
{
  if(m_sprite_id != -1)
    return true;
  return false;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void sObject::create(int sprite_id)
{
  m_sprite_id = sprite_id;
  PA_CreateSprite(0, m_sprite_id, m_sprite, OBJ_SIZE_16X16, 1, m_palette_index, m_x, m_y);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void sObject::destroy(void)
{
  if(m_sprite_id != -1)
  {
    PA_StopSpriteAnim(0, m_sprite_id);
    PA_DeleteSprite(0, m_sprite_id);
    m_sprite_id = -1;
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int sObject::get_sprite_id()
{
  return m_sprite_id;
}