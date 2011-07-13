#include "object-controller.h"

#include <PA9.h>

#include "spritecontroller.h"

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cObjectController::cObjectController(int x, int y) :
    m_x(x),
    m_y(y)
{
  m_sprite = NULL;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cObjectController::convert_from_palib_to_size(int param1, int param2)
{
  if(param1 == 0)
  {
    switch(param2)
    {
      case 0:
        m_h = m_w = 8;
      break;
      case 1:
        m_h = m_w = 16;
      break;
      case 2:
        m_h = m_w = 32;
      break;
      case 3:
        m_h = m_w = 64;
      break;
    }
  }
  else if(param1 == 1)
  {
    switch(param2)
    {
      case 0:
        m_h = 16;
        m_w = 8;
      break;
      case 1:
        m_h = 32;
        m_w = 8;
      break;
      case 2:
        m_h = 32;
        m_w = 16;
      break;
      case 3:
        m_h = 64;
        m_w = 32;
      break;
    }
  }
  else if(param1 == 2)
  {
    switch(param2)
    {
      case 0:
        m_h = 8;
        m_w = 16;
      break;
      case 1:
        m_h = 8;
        m_w = 32;
      break;
      case 2:
        m_h = 16;
        m_w = 32;
      break;
      case 3:
        m_h = 32;
        m_w = 64;
      break;
    }
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cObjectController::set_size(int param1, int param2)
{
  m_param1 = param1;
  m_param2 = param2;

  convert_from_palib_to_size(param1, param2);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int cObjectController::get_center()
{
  return m_x;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int cObjectController::get_left()
{
  return m_x - (m_h/2);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
int cObjectController::get_right()
{
  return m_x + (m_h/2);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cObjectController::create(int offset, int sprite_index)
{
  m_sprite_index = sprite_index;
//  m_palette_index = palette_index;
  if(!m_sprite)
  {
    m_sprite = new SpriteController(0, sprite_index);
    m_sprite->sprid = sprite_index;
    m_sprite->create((void *)m_sprite_pointer, m_param1, m_param2, m_palette_index);
    m_sprite->move(m_x, m_y);
    m_sprite->addAnimation(0,0,0);
    m_sprite->priority(0);
    m_sprite->beginAnimation(0);
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cObjectController::draw(int offset)
{
  m_sprite->move(get_left()-offset, m_y);
  m_sprite->render();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cObjectController::on_screen(int offset)
{
  if(get_right() > offset && get_left() < (offset+256))
  {
    char message[1024];
    sprintf(message,"offset, right, left: %d %d %d     ",offset, get_right(), get_left());
    nocashMessage(message);
    PA_OutputText(1,1,m_sprite_index, "%s", message);

    return true;
  }
  return false;
}

void cObjectController::destroy()
{
  if(m_sprite)
  {
    char message[1024];
    sprintf(message,"destroyed!!");
    nocashMessage(message);
    PA_OutputText(1,1,10, "%s", message);

    m_sprite->destroy();
    delete m_sprite;
    m_sprite = NULL;
  }
}
