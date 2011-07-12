#include "scroll-engine.h"

#include "all_gfx.h" // File with all the gfx compiled with the game

#include "global-data.h"
#include "level-data.h"
#include "item-data.h"
#include "object-controller.h"

int timer = 0;

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void millisecond_timer_function()
{
  timer++;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::set_global_data(const sGlobalData *global_data)
{
  m_global_data = global_data;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::load_graphics()
{
  for(unsigned int i(0); i < m_level_data_vector[m_current_level]->m_backgrounds.size(); ++i)
  {
    PA_LoadBackground(0, // screen
                      i, // background id
                      m_level_data_vector[m_current_level]->m_backgrounds[i]);
  }
  m_sprite_index = m_palette_index = 0;

  sLevelData *current_level = m_level_data_vector[m_current_level];
  std::list<cObjectController *> &m_objects = current_level->get_objects();

  m_alpha = m_objects.end();
  m_beta = m_objects.end();

  {
    std::list<cObjectController *>::iterator it;
    for(it = m_objects.end(); ; --it)
    {
      cObjectController *object = *it;
      if(object->get_right() > 0 && object->get_left() < 255) // object is on screen
      {
        m_beta = it;
        break;
      }
      if(it == m_objects.begin())
        break;
    }

    for(it = m_objects.begin(); it != m_objects.end(); ++it)
    {
      cObjectController *object = *it;
      if(object->get_right() > 0 && object->get_left() < 255) // object is on screen
      {
        m_alpha = it;
        break;
      }
    }
  }

  {
    std::list<cObjectController *>::iterator it, iend;
    iend = m_beta;
    iend++;
    for(it = m_alpha; it != iend; ++it)
    {
      cObjectController *object = *it;
      object->on_screen(0, m_sprite_index++, m_palette_index++);
    }
  }

  //m_collision_controller->load_collision_map(m_level_data_vector[m_current_level]->m_collision);
//  m_level_data_vector[m_current_level].m_backgrounds;
//  (sLevelData).

  PA_InitParallaxX(0, // Screen
                   screenSizeX, // Parallax speed for Background 0. 0 is no parallax
                   screenSizeX,
                   256,
                   0);

  int SMALL_MARIO_ANIM_SPEED = 10;

//  m_item_controller = new cItemController<tDefinedType>();
//  {
//    sItemData *item = m_level_data_vector[m_current_level]->m_items[0];
//    PA_LoadSpritePal(0,
//                     2, // Mudar pra uma variavel que mantenha a quantidade de paletas instanciadas
//                     (void *)item->m_palette_pointer);
//    m_item_controller->spr.sprid = 2;
//    m_item_controller->spr.pos.x = 0;
//    m_item_controller->spr.pos.y = 0;
//    m_item_controller->spr.create((void *)item->m_sprite_pointer, item->m_h, item->m_w, 2);
//    int x = item->m_x*8;
//    if(x >= 255)
//      x = 254;
//    m_item_controller->spr.move(x, item->m_y*8);
//    m_item_controller->spr.addAnimation(0,0,0); // Drag
//    m_item_controller->spr.priority(0);
//    m_item_controller->spr.beginAnimation(0);
//  }

  PA_LoadSpritePal(0, // Screen
                   m_palette_index, // Palette id
                   (void*) SuperMarioClone_Pal); // Pointer to load from

  m_player->spr.sprid = m_sprite_index++;
  m_player->spr.create((void *)(SuperMarioClone_Sprite), OBJ_SIZE_16X16, m_palette_index++);
  m_player->spr.move(0, screenSizeY-tileSizeY*5);
  m_player->spr.priority(0);
  m_player->spr.addAnimation(0,3,SMALL_MARIO_ANIM_SPEED); // Walking
  m_player->spr.addAnimation(4,4,0); // Drag
  m_player->spr.addAnimation(5,5,0); // Jumping
  m_player->spr.addAnimation(6,9,SMALL_MARIO_ANIM_SPEED); // Swimming
  m_player->spr.beginAnimation(0);

  m_collision_controller->addCollideablePlayer(m_player);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::init()
{
  // Initialize the text system
  PA_InitText(1, 0);

  load_resources(m_level_data_vector);

  m_current_level = 0;

  m_player = new cPlayerController<tDefinedType>(Vector2<tDefinedType>(0, 0),
                                        tileSizeXmult,
                                        tileSizeYmult,
                                        0,
                                        1,
                                        m_level_data_vector[m_current_level]);
  m_collision_controller = new cCollisionController<tDefinedType>(m_level_data_vector[m_current_level]);

  load_graphics();

  TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
  TIMER_DATA(1) = TIMER_FREQ_1024(1000);
  irqSet(IRQ_TIMER1, millisecond_timer_function);
  irqEnable(IRQ_TIMER1);

  m_timer = 0;
  m_old_timer = 0;
  m_controller_timer = 0;
  m_game_action_timer = 0;

#ifdef _DEBUG
  m_frame_count = 0;
#endif
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::render()
{
#ifdef _DEBUG
  char message[1024];
  sprintf(message,"worldMax: %d",worldMaxX);
  nocashMessage(message);
  PA_OutputText(1,1,3, "%s", message);
  sprintf(message,"pos: x %d y %d",m_player.getPos().x, m_player.getPos().y);
  nocashMessage(message);
  PA_OutputText(1,1,4, "%s", message);
  Vector2<tDefinedType> d;
  d = m_player.getPos() - m_player.getOldPos();
  sprintf(message,"dx %d dy %d",d.x, d.y);
  PA_OutputText(1,1,6, "%s       ", message);
#endif

  m_level_data_vector[m_current_level]->m_scrolled = m_player->getParallaxX();
  PA_ParallaxScrollX(0, // Screen
                     m_level_data_vector[m_current_level]->m_scrolled);
  m_player->Draw();
  {
    //sLevelData *current_level = m_level_data_vector[m_current_level];
    //std::list<cObjectController *> &m_objects = current_level->get_objects();
    std::list<cObjectController *>::iterator it, iend;
    iend = m_beta; iend++;
    for(it = m_alpha; it != iend; ++it)
    {
      cObjectController *object = *it;
      object->draw();
    }
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
bool cScrollEngine::update()
{
  // TODO(renatolond, 2011-06-09) Make this global timer go away
  m_timer = timer;
  double fTime;
  fTime = (m_timer - m_old_timer) / 1000.0;
  m_old_timer = m_timer;

#ifdef _DEBUG
  m_frame_count++;
#endif
  if(m_timer - m_controller_timer > m_global_data->miliseconds_between_input_cycles)
  {
      m_controller_timer = m_timer;
      if (Pad.Held.Right)
      {
          m_player->accelerateRight();
      }
      else if (Pad.Held.Left)
      {
          m_player->accelerateLeft();
      }

      if(Pad.Held.Up)
      {
          m_player->accelerateUp(m_timer);
      }
  }
  if(m_timer - m_game_action_timer > m_global_data->miliseconds_between_game_cycles)
  {
      m_game_action_timer = m_timer;
  }
  m_player->IntegrateVerlet();
  m_collision_controller->check_for_collisions(m_level_data_vector[m_current_level]->m_scrolled,
                                              0); // Not scrolling over y-axis
  {
    std::list<cObjectController *>::iterator it, iend;
    iend = m_beta; iend++;
    for(it = m_alpha; it != iend; ++it)
    {
      cObjectController *object = *it;
      object->update(m_level_data_vector[m_current_level]->m_scrolled);
    }
  }

  return true;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cScrollEngine::cScrollEngine()
{
  m_player = NULL;
  m_collision_controller = NULL;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cScrollEngine::~cScrollEngine()
{
  if(m_player)
    delete m_player;
  if(m_collision_controller)
    delete m_collision_controller;
}
