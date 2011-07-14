#include "player_controller.h"

#include <PA9.h>

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cPlayerController::cPlayerController()
{
  m_x = m_y = 0;
  m_vel_x = m_vel_x = 0;
  m_jumping = false;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cPlayerController::touching_ground()
{
  if(m_y >= 160.0)
    return true;
  else
    return false;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::create_sprite(int sprite_id, void *sprite, int palette_id, int x, int y)
{
  m_x = x;
  m_y = y;
  m_sprite_id = sprite_id;
  PA_CreateSprite(0, m_sprite_id, sprite, OBJ_SIZE_16X16, 1, palette_id, x, y);
}

void cPlayerController::move(int screen_scrolled)
{
  PA_SetSpriteXY(0, m_sprite_id, m_x-screen_scrolled, m_y);
}
