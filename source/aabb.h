#ifndef AABB_H
#define AABB_H

class cAABB
{
public:
    cAABB();
    virtual void report_collision_vs_world(int x, int y, double dx, double dy) = 0;
};

#endif // AABB_H
