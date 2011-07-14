#ifndef SCROLLENGINE_H
#define SCROLLENGINE_H

#include <PA9.h>

#include <vector>
#include <list>

#include "collisioncontroller.h"
#include "playercontroller.h"
#include "item-controller.h"

struct sGlobalData;
struct cObjectController;

void load_resources(std::vector<sLevelData *>& level_data_vector);

class cScrollEngine : public PA::Application
{
  /** TODO */
  cPlayerController<tDefinedType> *m_player;

  /** TODO */
  cCollisionController<tDefinedType> *m_collision_controller;

  /** TODO */
  const sGlobalData *m_global_data;

  /** TODO */
  std::vector<sLevelData *> m_level_data_vector;

  /** TODO */
  std::list<cObjectController *>::iterator m_alpha, m_beta;

  /** TODO */
  int m_sprite_index;

  /** TODO */
  int m_palette_index;

  /** TODO */
  int m_current_level;

  /** TODO */
  int m_current_player;

  /** TODO */
  int m_timer;

  /** TODO */
  int m_old_timer;

  /** TODO */
  int m_controller_timer;

  /** TODO */
  int m_game_action_timer;

#ifdef _DEBUG
  int m_frame_count;
#endif

  /**
   * @brief Carrega os graficos que serao usados durante o jogo
   */
  void load_graphics();

  /**
   * @brief Avisa aos objetos visiveis para atualizar suas posicoes e se desenhar
   */
  void draw_visible_objects();

 public:

  /**
   * @brief TODO
   */
  cScrollEngine();

  /**
   * @brief TODO
   */
  ~cScrollEngine();

  /**
   * @brief TODO
   *
   * @param[in] global_data TODO
   */
  void set_global_data(const sGlobalData *global_data);

  /**
   * @brief TODO
   */
  void init();

  /**
   * @brief TODO
   */
  void render();

  /**
   * @brief TODO
   */
  bool update();
};

#endif // SCROLLENGINE_H
