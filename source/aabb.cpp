#include "aabb.h"

#include "PA9.h"

cAABB::cAABB()
{
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
sAnimation::sAnimation(int start_frame, int end_frame, int base_velocity)
{
  m_start_frame = start_frame;
  m_end_frame = end_frame;
  m_base_velocity = base_velocity;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAABB::add_animation(int start_frame, int end_frame, int base_velocity)
{
  m_animations.push_back(sAnimation(start_frame, end_frame, base_velocity));
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAABB::begin_animation(unsigned int index)
{
  if(m_current_animation == index)
    return;
  if(index >= m_animations.size())
    return;

  m_current_animation = index;

  int animation_type = ANIM_UPDOWN;

  sAnimation &anim = m_animations[m_current_animation];

  PA_StartSpriteAnimEx(0, m_sprite_id, anim.m_start_frame, anim.m_end_frame, anim.m_base_velocity,
                       animation_type,
                       -1); // infinite cycles
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cAABB::stop_animation()
{
  PA_StartSpriteAnim(0, m_sprite_id, 0, 0, 0);
  PA_StopSpriteAnim(0, m_sprite_id);
  m_current_animation = -1;
}
