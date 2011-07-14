#ifndef OBJECT_H
#define OBJECT_H

class sObject
{
  int m_sprite_id;
public:
  sObject();
  void *m_sprite;
  int m_palette_index;
  int m_x;
  int m_y;

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
};

#endif // OBJECT_H
