#ifndef AABB_H
#define AABB_H

#include <vector>

struct sAnimation
{
  int m_start_frame;
  int m_end_frame;
  int m_base_velocity;
  sAnimation(int start_frame, int end_frame, int base_velocity);
};

class cAABB
{
protected:
  int m_sprite_id;

  /** TODO */
  std::vector<sAnimation> m_animations;

  /** TODO */
  unsigned int m_current_animation;

public:
  double m_x;
  double m_y;
  double m_h;
  double m_w;
  bool m_danger;
  cAABB();
  virtual void report_collision_vs_world(int x, int y, double dx, double dy) = 0;

  /**
   * @brief TODO
   *
   * @param start_frame TODO
   * @param end_frame TODO
   * @param base_velocity TODO
   */
  void add_animation(int start_frame, int end_frame, int base_velocity);

  /**
   * @brief TODO
   *
   * @param index TODO
   */
  void begin_animation(unsigned int index);

  /**
   * @brief TODO
   */
  void stop_animation();

  /**
   * @brief TODO
   */
  virtual void die() = 0;

  /**
   * @brief TODO
   */
  virtual bool dead() = 0;
};

#endif // AABB_H
