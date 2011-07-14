#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

class cPlayerController
{
  int m_sprite_id;
public:
  double m_vel_x;
  double m_vel_y;
  double m_x;
  double m_y;
  bool m_jumping;
  cPlayerController();
  bool touching_ground();
  void create_sprite(int sprite_id, void *sprite, int palette_id, int x, int y);
  void move(int screen_scrolled);
};

#endif // PLAYER_CONTROLLER_H
