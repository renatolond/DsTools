#ifndef COLLISION_CONTROLLER_H
#define COLLISION_CONTROLLER_H

#include <PA_BgStruct.h> // Apparently no forward declaration possible

class cPlayerController;
class cTileMapCell;

class cCollisionController
{
  cTileMapCell **m_map;
  cPlayerController *m_player;
  int m_max_world_height;
  int m_min_world_height;
  int m_max_world_width;
  int m_min_world_width;
public:
  /**
   * @brief TODO
   */
  cCollisionController();

  /**
   * @brief TODO
   *
   * @param x_scroll TODO
   * @param y_scroll TODO
   */
  void check_for_collisions(const int &x_scroll, const int &y_scroll);

  /**
   * @brief TODO
   *
   * @param bg TODO
   */
  void load_tile_map(const PA_BgStruct &bg);

  /**
   * @brief TODO
   *
   * @param map TODO
   * @param player TODO
   * @param j TODO
   * @param i TODO
   */
  void collide_vs_tile(cTileMapCell **map, cPlayerController *player, int j, int i) const;

  /**
   * @brief TODO
   *
   * @param player TODO
   */
  void set_player(cPlayerController *player);
};

#endif // COLLISION_CONTROLLER_H
