#include "player_controller.h"

#include <PA9.h>

#include "tilemapcell.h"

#include "scroll_engine.h"

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cPlayerController::cPlayerController(cScore *score)
{
  // TODO(renatolond, 2011-07-15) get this from the sprite.
  m_w = m_h = 8;
  m_x = m_y = 0;
  m_vel_x = m_vel_y = 0;
  m_jumping = false;
  m_score = score;
  m_current_animation = -1;
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
  PA_CreateSprite(0, m_sprite_id, sprite, OBJ_SIZE_16X16, 1, palette_id, x-m_w, y-m_h);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::move(int screen_scrolled)
{
  PA_SetSpriteXY(0, m_sprite_id, (m_x-m_w)-screen_scrolled, (m_y-m_h));
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::collide_vs_world_bounds(int world_min_width, int world_max_width,
                                                int world_min_height, int world_max_height)
{
  int x, y;

  x = world_min_width - (m_x - m_w);
  // collision against left side
  if(x > 0)
  {
    report_collision_vs_world(x, 0, 1, 0);
  }
  else
  {
    x = (m_x + m_w) - world_max_width;

    // collision against right side
    if(x > 0)
      report_collision_vs_world(-x, 0, -1, 0);
  }

  y = world_min_height - (m_y - m_h);
  // collision against upper bounds
  if(y > 0)
  {
    report_collision_vs_world(0, y, 0, 1);
  }
  else
  {
    // death?
    y = (m_y + m_h) - world_max_height;
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
  int dx, dy;
  int x, y;
  dx = m_x - tile.pos.x;
  x = (tile.xw + m_w) - fabs(dx);

  if(x > 0)
  {
    dy = m_y - tile.pos.y;
    y = (tile.yw + m_h) - fabs(dy);

    if(y > 0)
    {
      if(x < y)
      {
        if(dx < 0)
        {
          x *= -1;
          y = 0;
        }
        else
          y = 0;
      }
      else
      {
        if(dy < 0)
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

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cPlayerController::collide_vs_aabb(cAABB &aabb)
{
  int dx, dy;
  int x, y;

  dx = m_x - aabb.m_x;
  x = (m_w+aabb.m_w) - fabs(dx);

  if(x > 0)
  {
    dy = m_y - aabb.m_y;
    y = (m_h+aabb.m_h) - fabs(dy);

    if(y > 0)
    {
      if(x < y)
      {
        if(dx < 0)
        {
          x *= -1;
          y = 0;
        }
        else
          y = 0;
      }
      else
      {
        if(dy < 0)
        {
          x = 0;
          y *= -1;
        }
        else
          x = 0;
      }

      double temp;
      temp = sqrt(x*x + y*y);
      if(m_danger == false)
      {
        if(y > 0 && !aabb.dead())
        {
          aabb.die();
          m_score->plus100();
        }
      }
      report_collision_vs_world(x, y, x/temp, y/temp);
    }
  }
}

void cPlayerController::check_animation()
{
  if(m_vel_x > 0)
    PA_SetSpriteHflip(0, m_sprite_id, false);
  else if(m_vel_x < 0)
    PA_SetSpriteHflip(0, m_sprite_id, true);

  if(m_vel_x*m_vel_x > 0.0)
    begin_animation(0);
  else if(!touching_ground())
    begin_animation(2);
  else
    stop_animation();
}

void cPlayerController::die()
{

}

bool cPlayerController::dead()
{
  return false;
}
