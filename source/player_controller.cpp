#include "player_controller.h"

#include <PA9.h>

#include "tilemapcell.h"

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cPlayerController::cPlayerController()
{
  m_x = m_y = 0;
  m_vel_x = m_vel_y = 0;
  m_jumping = false;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cPlayerController::touching_ground()
{
  return m_touching_ground;
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

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::move(int screen_scrolled)
{
  PA_SetSpriteXY(0, m_sprite_id, m_x-screen_scrolled, m_y);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::collide_vs_world_bounds(int world_min_width, int world_max_width,
                                                int world_min_height, int world_max_height)
{
  int x, y;
  int m_w = 8;
  int m_h = 8;

//  int world_min_width = 0;
//  int world_max_width = 256;
//  int world_min_height = 0;
//  int world_max_height = 192;

  x = world_min_width - m_x;
  // collision against left side
  if(x > 0)
  {
    report_collision_vs_world(x, 0, 1, 0);
  }
  else
  {
    x = (m_x + m_w*2) - world_max_width;

    // collision against right side
    if(x > 0)
      report_collision_vs_world(-x, 0, -1, 0);
  }

  y = world_min_height - m_y;
  // collision against upper bounds
  if(y > 0)
  {
    report_collision_vs_world(0, y, 0, 1);
  }
  else
  {
    y = (m_y + m_h*2) - world_max_height;
    if(y > 0)
      report_collision_vs_world(0, -y, 0, -1);
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::report_collision_vs_world(int x, int y, double dx, double dy)
{
  m_x += x;
  m_y += y;
  if(y < 0)
    m_touching_ground = true;
//  m_vel_x *= dx;
//  m_vel_y *= dy;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::collide_vs_tile(cTileMapCell &tile)
{
  int m_w = 8;
  int m_h = 8;

  int dx, dy;
  int x, y;
  dx = m_x - tile.pos.x;
  x = tile.xw + m_w*2 - fabs(dx);

  if (x > 0)
  {
    dy = m_y - tile.pos.y;
    y = tile.yw + m_h*2 - fabs(dy);

    if (y > 0)
    {
      if (x < y)
      {
        if (dx < 0)
        {
          x *= -1;
          y = 0;
        }
        else
          y = 0;
      }
      else
      {
        if (dy < 0)
        {
          x = 0;
          y *= -1;
        }
        else
          x = 0;
      }

      tile.projAABB(x, y, *this);

      //ResolveBoxTile(x, y, *this, tile);
    }
  }
}
