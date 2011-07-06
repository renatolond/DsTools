#ifndef SCROLLENGINE_H
#define SCROLLENGINE_H

#include <PA9.h>

#include <vector>

#include "collisioncontroller.h"
#include "playercontroller.h"
#include "item-controller.h"

struct sGlobalData;

void load_resources(std::vector<sLevelData *>& level_data_vector);

class cScrollEngine : public PA::Application
{
  cPlayerController<tDefinedType> *m_player;
  cCollisionController<tDefinedType> *m_collision_controller;
  cItemController<tDefinedType> *m_item_controller;

  const sGlobalData *m_global_data;

  std::vector<sLevelData *> m_level_data_vector;

  int m_current_level;
  int m_current_player;

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
