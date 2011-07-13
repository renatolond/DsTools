#ifndef OBJECTCONTROLLER_H
#define OBJECTCONTROLLER_H

class SpriteController;

class cObjectController
{
  /** TODO */
  int m_x;

  /** TODO */
  int m_y;

  /** TODO */
  int m_h;

  /** TODO */
  int m_w;

  /** TODO */
  int m_param1;

  /** TODO */
  int m_param2;

  /** TODO */
  SpriteController *m_sprite;

  /** TODO */
  int m_sprite_index;

 public:
  /** TODO */
  const void *m_sprite_pointer;

  /** TODO */
  int m_palette_index;

  /**
   * @brief TODO
   *
   * @param[in] param1 TODO
   * @param[in] param2 TODO
   */
  void set_size(int param1, int param2);

  /**
   * @brief TODO
   *
   * @return
   */
  int get_center(void);

  /**
   * @brief TODO
   *
   * @return
   */
  int get_left(void);

  /**
   * @brief TODO
   *
   * @return
   */
  int get_right(void);

  /**
   * @brief TODO
   *
   * @param[in] offset TODO
   * @param[in] sprite_index TODO
   * @param[in] palette_index TODO
   */
  void create(int offset, int sprite_index);

  /**
   * @brief TODO
   *
   * @param[in] offset TODO
   * @return
   */
  bool on_screen(int offset);

  /**
   * @brief TODO
   *
   * @param[in] offset TODO
   */
  void draw(int offset);

  /**
   * @brief TODO
   */
  void destroy(void);

  /**
   * @brief TODO
   *
   * @param[in] param1 TODO
   * @param[in] param2 TODO
   */
  void convert_from_palib_to_size(int param1, int param2);

  /**
   * @brief TODO
   *
   * @param[in] x TODO
   * @param[in] y TODO
   */
  cObjectController(int x, int y);
};

#endif // OBJECTCONTROLLER_H
