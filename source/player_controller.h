#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include "aabb.h" // Base class

class cTileMapCell;

class cPlayerController : public cAABB
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
  void collide_vs_world_bounds(void);
  void report_collision_vs_world(int x, int y, double dx, double dy);
  void collide_vs_tile(cTileMapCell& tile_map_cell);
};

#endif // PLAYER_CONTROLLER_H
