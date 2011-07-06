#ifndef ENEMYDATA_H
#define ENEMYDATA_H

enum eEnemyMovement
{
  STRAIGHT_FALL
};

struct sEnemyData
{
  int m_x, m_y, m_h, m_w;
  const void *m_sprite_pointer;
  const void *m_palette_pointer;
  eEnemyMovement m_enemy_movement;
  void set_size(int h, int w);
};

#endif // ENEMYDATA_H
