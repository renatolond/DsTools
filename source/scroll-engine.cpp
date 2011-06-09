#include "scroll-engine.h"

#include "all_gfx.h" // File with all the gfx compiled with the game

#include "global-data.h"
#include "level-data.h"

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
  PA_LoadSpritePal(0, // Screen
                   1, // Palette id
                   (void*) small_mario_Pal); // Pointer to load from

  PA_LoadBackground(0, // Screen
                    0, // Background id
                    &bgtool0);
  PA_InitParallaxX(0, // Screen
                   screenSizeX, // Parallax speed for Background 0. 0 is no parallax
                   screenSizeX,
                   256,
                   0);

  int SMALL_MARIO_ANIM_SPEED = 10;

  m_player.spr.create((void *)(small_mario_Sprite), OBJ_SIZE_16X16, 1);
  m_player.spr.move(0, screenSizeY-tileSizeY*5);
  m_player.spr.priority(0);
  m_player.spr.addAnimation(0,3,SMALL_MARIO_ANIM_SPEED); // Walking
  m_player.spr.addAnimation(4,4,0); // Drag
  m_player.spr.addAnimation(5,5,0); // Jumping
  m_player.spr.addAnimation(6,9,SMALL_MARIO_ANIM_SPEED); // Swimming
  m_player.spr.beginAnimation(0);

  m_collision_controller.addCollideablePlayer(&m_player);
  m_collision_controller.loadTileMap();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cScrollEngine::init()
{
  // Initialize the text system
  PA_InitText(1, 0);
  m_level_data.m_world_min_height = 0;
  m_level_data.m_world_min_width = 0;
  m_level_data.m_world_max_height = bgtool0.height*multiplier;
  m_level_data.m_world_max_width = bgtool0.width*multiplier;
  m_level_data.m_scrolled = 0;

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

  m_level_data.m_scrolled = m_player.getParallaxX();
  PA_ParallaxScrollX(0, // Screen
                     m_level_data.m_scrolled);
  m_player.Draw();
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
          m_player.accelerateRight();
      }
      else if (Pad.Held.Left)
      {
          m_player.accelerateLeft();
      }

      if(Pad.Held.Up)
      {
          m_player.accelerateUp(m_timer);
      }
  }
  if(m_timer - m_game_action_timer > m_global_data->miliseconds_between_game_cycles)
  {
      m_game_action_timer = m_timer;
  }
  m_player.IntegrateVerlet();
  m_collision_controller.check_for_collisions(m_level_data.m_scrolled,
                                              0); // Not scrolling over y-axis
  return true;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cScrollEngine::cScrollEngine() :
  m_player(Vector2<tDefinedType>(0, 0), // Initial position
           tileSizeXmult, // width
           tileSizeYmult, // height
           0, // Sprite screen
           1, // Sprite number
           &m_level_data),
  m_collision_controller(&m_level_data)

{


}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cScrollEngine::~cScrollEngine()
{
}
