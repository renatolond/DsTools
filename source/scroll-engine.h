#ifndef SCROLLENGINE_H
#define SCROLLENGINE_H

#include <PA9.h>

#include "collisioncontroller.h"
#include "playercontroller.h"
#include "level-data.h"

struct sGlobalData;

class cScrollEngine : public PA::Application
{
  cPlayerController<tDefinedType> m_player;
  cCollisionController<tDefinedType> m_collision_controller;

  const sGlobalData *m_global_data;

  sLevelData m_level_data;

  int m_timer;
  int m_old_timer;
  int m_controller_timer;
  int m_game_action_timer;

#ifdef _DEBUG
  int m_frame_count;
#endif

  /**
   * @brief Carrega os graficos que serao usados durante o jogo
   */
  void load_graphics();

 public:

  cScrollEngine();
  ~cScrollEngine();

  void set_global_data(const sGlobalData *global_data);

  void init();
  void render();
  bool update();
};

#endif // SCROLLENGINE_H