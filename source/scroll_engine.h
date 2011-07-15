#ifndef SCROLL_ENGINE_H
#define SCROLL_ENGINE_H

#include <PA9.h>

#include <vector>

#define DEFAULT_PLAYTIME 300
#define MILISEC_BETWEEN_GAME_CICLES 33

class cCollisionController;
class cPlayerController;

class sLevelData;

class cScore
{
  int *m_score;
public:
  cScore(int *score) :
    m_score(score)
  {
  }

  void plus100() { (*m_score) += 100; }
};

class cScrollEngine : public PA::Application
{
  cPlayerController *m_player;
  cCollisionController *m_current_level_collision;
  std::vector<sLevelData *> m_level_data_vector;
  int m_current_level;
  int m_screen_scrolled;

  int m_game_action_timer;
  int m_timer;
  int m_old_timer;
  int m_controller_timer;

  int m_score;

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
  void update_display_hud(void);

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
