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
  bool m_touching_ground;

  /**
   * @brief TODO
   */
  cPlayerController();

  /**
   * @brief TODO
   */
  bool touching_ground();

  /**
   * @brief TODO
   *
   * @param sprite_id TODO
   * @param sprite TODO
   * @param palette_id TODO
   * @param x TODO
   * @param y TODO
   */
  void create_sprite(int sprite_id, void *sprite, int palette_id, int x, int y);

  /**
   * @brief TODO
   *
   * @param screen_scrolled TODO
   */
  void move(int screen_scrolled);

  /**
   * @brief TODO
   *
   * @param world_min_width TODO
   * @param world_max_width TODO
   * @param world_min_height TODO
   * @param world_max_height TODO
   */
  void collide_vs_world_bounds(int world_min_width, int world_max_width, int world_min_height,
                               int world_max_height);

  /**
   * @brief TODO
   *
   * @param x TODO
   * @param y TODO
   * @param dx TODO
   * @param dy TODO
   */
  void report_collision_vs_world(int x, int y, double dx, double dy);

  /**
   * @brief TODO
   *
   * @param tile TODO
   */
  void collide_vs_tile(cTileMapCell& tile);
};

#endif // PLAYER_CONTROLLER_H
