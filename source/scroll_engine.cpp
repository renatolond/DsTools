#include "scroll_engine.h"

#include "level_data.h"
#include "player_controller.h"
#include "object.h"
#include "resources.h"

cScrollEngine::cScrollEngine()
{
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::init()
{
  // Initialize the text system
  PA_InitText(1, 0);

  memset(m_occupied_sprites, 0, sizeof(m_occupied_sprites));

  load_resources(m_level_data_vector);

  m_current_level = 0;

  load_current_level();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::render()
{
  PA_ParallaxScrollXY(0, m_screen_scrolled, 0);
  m_player->move(m_screen_scrolled);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cScrollEngine::update()
{
  check_for_player_movement();
  check_for_collisions();
  check_for_screen_scrolling();

  return true;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::check_for_player_movement()
{
  double speed = 1; // debug only
  double max_speed = 2;
  double gravity = (60.0/256);
  double jump_vel = -(1500.0/256);
  double jump_low_limit_vel = -(400.0/256);
  if(Pad.Newpress.Right)
  {
    // mario.info.hitbox.flipped = 0;
  }
  else if(Pad.Newpress.Left)
  {
    // mario.info.hitbox.flipped = 1;
  }

  if((Pad.Newpress.A) && m_player->touching_ground())
  {
    m_player->m_vel_y = jump_vel;
    m_player->m_jumping = true;
  }

  if(m_player->m_jumping && !Pad.Held.A && (m_player->m_vel_y < jump_low_limit_vel))
  {
    m_player->m_vel_y = jump_low_limit_vel;
  }

  int side_mario_speeds = Pad.Held.Right - Pad.Held.Left;

  m_player->m_x += side_mario_speeds*(max_speed*speed); // Look into it

  if(!m_player->touching_ground())
  {
    m_player->m_vel_y += (gravity*speed);
  }
  m_player->m_y += m_player->m_vel_y * speed;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::load_current_level()
{
  for(unsigned int i(0); i < m_level_data_vector[m_current_level]->m_backgrounds.size(); ++i)
  {
    PA_LoadBackground(0, // screen
                      i, // background id
                      m_level_data_vector[m_current_level]->m_backgrounds[i]);
  }

  PA_InitParallaxX(0, // Screen
                   256, // Parallax speed for Background 0. 0 is no parallax
                   256,
                   256,
                   256);
  PA_InitParallaxY(0, // Screen
                   256, // Parallax speed for Background 0. 0 is no parallax
                   256,
                   256,
                   256);

  m_screen_scrolled = 0;

  m_player->create_sprite(get_unoccupied_sprite_id(),
                          m_level_data_vector[m_current_level]->m_player_sprite,
                          m_level_data_vector[m_current_level]->m_player_palette_index,
                          m_level_data_vector[m_current_level]->m_player_start_x,
                          m_level_data_vector[m_current_level]->m_player_start_y);

  std::vector<void *> &m_palettes = m_level_data_vector[m_current_level]->m_palettes;
  int i = 0;
  for(std::vector<void *>::iterator it = m_palettes.begin(); it != m_palettes.end(); ++it)
  {
    PA_LoadSpritePal(0, // Screen
                     i++, // Palette id
                     (void*) (*it)); // Pointer to load from
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int cScrollEngine::get_unoccupied_sprite_id()
{
  for(int i(0); i < 128; ++i)
  {
    if(!m_occupied_sprites[i])
    {
      m_occupied_sprites[i] = 1;
      return i;
    }
  }

  return -1; // Error. No more sprites available.
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::check_for_screen_scrolling()
{
  int half_screen_x = 130;
  int quarter_screen_x = 64;
  int max_world_x = 2048 - 128;
  int screen_x = 256;
  int object_x = 16;

  // If player is reached half screen
  if(((m_player->m_x - m_screen_scrolled) > half_screen_x) && (m_player->m_x < max_world_x))
  {
    // Screen starts scrolling.
    m_screen_scrolled = m_player->m_x - half_screen_x;
  }
  // But if player came before quarter screen
  else if(((m_player->m_x - m_screen_scrolled) < quarter_screen_x) &&
          (m_player->m_x > quarter_screen_x))
  {
    // screen starts unrolling.
    m_screen_scrolled = m_player->m_x - quarter_screen_x;
  }

  sLevelData *current_level_data = m_level_data_vector[m_current_level];
  std::vector<sObject *>& objects = current_level_data->m_objects;
  for(unsigned int i(0); i < objects.size(); ++i)
  {
    sObject *object = objects[i];

    // if object is on screen.
    if((object->m_x <= m_screen_scrolled + screen_x) &&
       (object->m_x >= m_screen_scrolled - object_x))
    {
      if(!object->exists())
        object->create(get_unoccupied_sprite_id());
      object->move(m_screen_scrolled);
    }
    // object is off screen, make sure it is destroyed.
    else
    {
      if(object->exists())
      {
        int sprite_id = object->get_sprite_id();
        object->destroy();
        m_occupied_sprites[sprite_id] = 0;
      }
    }
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::check_for_collisions()
{
  if(m_player->touching_ground())
  {
    m_player->m_vel_y = 0;
    //m_player->m_y += 2;
    m_player->m_jumping = 0;
  }
}
