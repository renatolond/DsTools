#include "object-controller.h"

#include <PA9.h>

#include "spritecontroller.h"

cObjectController::cObjectController(int x, int y) :
    m_x(x),
    m_y(y)
{
  m_sprite = NULL;
}

void cObjectController::set_size(int h, int w)
{
  m_h = h;
  m_w = w;
}

int cObjectController::get_center()
{
  return m_x;
}

int cObjectController::get_left()
{
  return m_x - (m_w/2);
}

int cObjectController::get_right()
{
  return m_x + (m_w/2);
}

void cObjectController::on_screen(int offset, int sprite_index, int palette_index)
{
  m_sprite_index = sprite_index;
  m_palette_index = palette_index;
  PA_LoadSpritePal(0,
                   palette_index,
                   (void *)m_palette_pointer);
  if(!m_sprite)
  {
    m_sprite = new SpriteController(0, sprite_index);
    m_sprite->sprid = sprite_index;
    m_sprite->create((void *)m_sprite_pointer, m_h, m_w, palette_index);
    m_sprite->move(m_x, m_y);
    m_sprite->addAnimation(0,0,0);
    m_sprite->priority(0);
    m_sprite->beginAnimation(0);
  }
}

void cObjectController::draw(void)
{
  m_sprite->render();
}

void cObjectController::update(int offset)
{
  // TODO(o que faze raqui?)
}
