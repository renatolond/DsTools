#include "collision_controller.h"

#include <PA9.h>

#include "player_controller.h"
#include "tilemapcell.h"

cCollisionController::cCollisionController()
{
  m_player = NULL;
  m_map = NULL;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cCollisionController::load_tile_map(const PA_BgStruct &bg)
{
  int tileSizeX = 8;
  int tileSizeY = 8;
  int tileSizeXmult = 8;
  int tileSizeYmult = 8;

  m_min_world_height = 0;
  m_min_world_width = 0;
  m_max_world_height = bg.height;
  m_max_world_width = bg.width;

  s16 *bgMap = (s16 *)bg.BgMap;
  m_map = new cTileMapCell*[bg.height/tileSizeY];
  for ( int i = 0 ; i < bg.height/tileSizeY ; i++ )
  {
    m_map[i] = new cTileMapCell[bg.width/tileSizeX];
    for ( int j = 0 ; j < bg.width/tileSizeX ; j++ )
    {
      m_map[i][j] = cTileMapCell(j*tileSizeXmult+(int)(tileSizeXmult/2),
                                 i*tileSizeYmult+(int)(tileSizeYmult/2),
                                 (int)(tileSizeXmult/2),
                                 (int)(tileSizeYmult/2));
      int index = j+i*(bg.width/tileSizeX);
      if (bgMap[index] == 55 || bgMap[index] == 56 || bgMap[index] == 57 || bgMap[index] == 58) // PLACEHOLDER!
      {
        m_map[i][j].SetState(TileEnum::full);
      }
      else
        m_map[i][j].SetState(TileEnum::empty);
    }
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
inline void cCollisionController::collide_vs_tile(cTileMapCell **m_map,
                                                cPlayerController *player,
                                                int j,
                                                int i) const
{
  int tileSizeXmult = 8;
  int tileSizeYmult = 8;
  //int m_world_max_width = 2000;
  //int m_world_max_height = 192;

  if ( i >= 0 && i < m_max_world_width/tileSizeXmult && j >= 0 &&
       j < m_max_world_height/tileSizeYmult )
    player->collide_vs_tile(m_map[j][i]);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cCollisionController::check_for_collisions(const int &x_scroll, const int &y_scroll)
{
  int tileSizeXmult = 8;
  int tileSizeYmult = 8;

  int playerTileX, playerTileY;//, playerTileY2;
  // TODO: Colisão com todos o bgmaps ou ao menos, com os delimitados pelo programador.
#ifdef _DEBUG
  s16 *bgMap = (s16 *)bgtool0.BgMap;
#endif

  if(!m_player)
    return;
  if(!m_map)
    return;

  m_player->m_touching_ground = false;

  playerTileX = m_player->m_x / tileSizeXmult;
#ifdef _DEBUG
  asm("mov r11,r11");
#endif
  playerTileY = m_player->m_y / tileSizeYmult;
#ifdef _DEBUG
  asm("mov r11,r11");
#endif
  collide_vs_tile(m_map, m_player, playerTileY+1, playerTileX);
  collide_vs_tile(m_map, m_player, playerTileY, playerTileX-1);
  collide_vs_tile(m_map, m_player, playerTileY, playerTileX);
  collide_vs_tile(m_map, m_player, playerTileY, playerTileX+1);
  collide_vs_tile(m_map, m_player, playerTileY-1, playerTileX-1);
  collide_vs_tile(m_map, m_player, playerTileY-1, playerTileX);
  collide_vs_tile(m_map, m_player, playerTileY-1, playerTileX+1);

  m_player->collide_vs_world_bounds(m_min_world_width, m_max_world_width, m_min_world_height,
                                    m_max_world_height);

#ifdef _DEBUG
  PA_OutputText(1, 1, 9,"Tile: %d      ", bgMap[(int)playerTileX+playerTileY*bgtool0.width/tileSizeX]);
  PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d %d %d     ", player->getPos().x, x_scroll, playerTileX, playerTileY, tileSizeYmult, player->getPos().y/tileSizeYmult);
#endif
  //    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
  //    {
  //        player->ceaseMovement();
  //    }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cCollisionController::set_player(cPlayerController *player)
{
  m_player = player;
}

