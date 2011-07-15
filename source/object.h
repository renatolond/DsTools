#ifndef OBJECT_H
#define OBJECT_H

#include "aabb.h" // Base class

class sObject : public cAABB
{
  bool m_dead;
public:
  sObject();
  void *m_sprite;
  int m_palette_index;

  /**
   * @brief TODO
   *
   * @param screen_scrolled TODO
   */
  void move(int screen_scrolled);

  /**
   * @brief TODO
   *
   * @return
   */
  bool exists(void);

  /**
   * @brief TODO
   *
   * @param sprite_id TODO
   */
  void create(int sprite_id);

  /**
   * @brief TODO
   */
  void destroy(void);

  /**
   * @brief TODO
   *
   * @return
   */
  int get_sprite_id();

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
   */
  void die();

  /**
   * @brief TODO
   */
  bool dead();
};

#endif // OBJECT_H
