#ifndef AABB_H
#define AABB_H

class cAABB
{
protected:
public:
  double m_x;
  double m_y;
  double m_h;
  double m_w;
  cAABB();
  virtual void report_collision_vs_world(int x, int y, double dx, double dy) = 0;
};

#endif // AABB_H
