#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

class SpriteController;

class cObjectController
{
  int m_x;
  int m_y;
  int m_h;
  int m_w;
  SpriteController *m_sprite;
  int m_sprite_index;
  int m_palette_index;
 public:
  const void *m_sprite_pointer;
  const void *m_palette_pointer;
  void set_size(int h, int w);
  int get_center(void);
  int get_left(void);
  int get_right(void);
  void on_screen(int offset, int sprite_index, int palette_index);
  void draw(void);
  void update(int offset);
  cObjectController(int x, int y);
};

#endif // OBJECTCONTROLLER_H
