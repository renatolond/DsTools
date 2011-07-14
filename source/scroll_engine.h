#ifndef SCROLL_ENGINE_H
#define SCROLL_ENGINE_H

#include <PA9.h>

#include <vector>

class cPlayerController;

class sLevelData;

class cScrollEngine : public PA::Application
{
  cPlayerController *m_player;
  std::vector<sLevelData *> m_level_data_vector;
  int m_current_level;
  int m_screen_scrolled;

  int m_occupied_sprites[128];

 public:
  /**
   * @brief TODO
   */
  cScrollEngine(void);

  /**
   * @brief TODO
   */
  void init(void);

  /**
   * @brief TODO
   */
  void render(void);

  /**
   * @brief TODO
   */
  bool update(void);

  /**
   * @brief TODO
   */
  void check_for_player_movement(void);

  /**
   * @brief TODO
   *
   * @param level_data TODO
   */
  void load_current_level();

  /**
   * @brief TODO
   *
   * @return TODO
   */
  int get_unoccupied_sprite_id(void);

  /**
   * @brief TODO
   */
  void check_for_screen_scrolling(void);

  /**
   * @brief TODO
   */
  void check_for_collisions(void);
};

#endif // SCROLL_ENGINE_H
