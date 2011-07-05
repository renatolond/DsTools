#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <PA9.h>

#include "all_gfx.h"

#include "level-data.h"
#include "spritecontroller.h"
#include "tilemapcell.h"
#include "playercontroller.h"

template <class T>
        class cCollisionController
{
    const sLevelData *m_level_data;
    cPlayerController<T> *player;
    TileMapCell<T> **map;
public:
    cCollisionController(const sLevelData *level_data);
    void check_for_collisions(const int &x_scroll, const int &y_scroll);
    void addCollideableSprite(SpriteController *s);
    void addCollideablePlayer(cPlayerController<T> *p);
//    void loadTileMap();
    void collideVsTile(TileMapCell<T> **map, cPlayerController<T> *player, int j, int i) const;
};

template <class T>
        cCollisionController<T>::cCollisionController(const sLevelData *level_data) :
          m_level_data(level_data)
{
}

template <class T>
        void cCollisionController<T>::addCollideableSprite(SpriteController *s)
{
}

template <class T>
        void cCollisionController<T>::addCollideablePlayer(cPlayerController<T> *p)
{
    player = p;
}

//template <class T>
//        void cCollisionController<T>::loadTileMap()
//{
//    s16 *bgMap = (s16 *)bgtool0.BgMap;
//    map = new TileMapCell<T>*[bgtool0.height/tileSizeY];
//    for ( int i = 0 ; i < bgtool0.height/tileSizeY ; i++ )
//    {
//        map[i] = new TileMapCell<T>[bgtool0.width/tileSizeX];
//        for ( int j = 0 ; j < bgtool0.width/tileSizeX ; j++ )
//        {
//            map[i][j] = TileMapCell<T>(j*tileSizeXmult+(T)(tileSizeXmult/2), i*tileSizeYmult+(T)(tileSizeYmult/2), (T)(tileSizeXmult/2), (T)(tileSizeYmult/2));
//            int index = j+i*(bgtool0.width/tileSizeX);
//            if (bgMap[index] == 60 || bgMap[index] == 61 || bgMap[index] == 62 || bgMap[index] == 63 ||
//                bgMap[index] == 19 || bgMap[index] == 20 || bgMap[index] == 25 || bgMap[index] == 26) // PLACEHOLDER!
//            {
//                map[i][j].SetState(TileEnum::full);
//            }
//            else
//                map[i][j].SetState(TileEnum::empty);
//        }
//    }
//}

template <class T>
        inline void cCollisionController<T>::collideVsTile(TileMapCell<T> **map,
                                                           cPlayerController<T> *player,
                                                           int j,
                                                           int i) const
{
    if ( i >= 0 && i < m_level_data->m_world_max_width/tileSizeXmult && j >= 0 &&
        j < m_level_data->m_world_max_height/tileSizeYmult )
        player->CollideVsTile(map[j][i]);
}

template <class T>
        void cCollisionController<T>::check_for_collisions(const int &x_scroll, const int &y_scroll)
{
    int playerTileX, playerTileY;//, playerTileY2;
    // TODO: Colisão com todos o bgmaps ou ao menos, com os delimitados pelo programador.
#ifdef _DEBUG
    s16 *bgMap = (s16 *)bgtool0.BgMap;
#endif

    playerTileX = player->getPos().x / tileSizeXmult;
#ifdef _DEBUG
    asm("mov r11,r11");
#endif
    playerTileY = player->getPos().y / tileSizeYmult;
#ifdef _DEBUG
    asm("mov r11,r11");
#endif
    collideVsTile(map, player, playerTileY+1, playerTileX);
    collideVsTile(map, player, playerTileY, playerTileX-1);
    collideVsTile(map, player, playerTileY, playerTileX);
    collideVsTile(map, player, playerTileY, playerTileX+1);
    collideVsTile(map, player, playerTileY-1, playerTileX-1);
    collideVsTile(map, player, playerTileY-1, playerTileX);
    collideVsTile(map, player, playerTileY-1, playerTileX+1);

    player->CollideVsWorldBounds();

#ifdef _DEBUG
    PA_OutputText(1, 1, 9,"Tile: %d      ", bgMap[(int)playerTileX+playerTileY*bgtool0.width/tileSizeX]);
    PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d %d %d     ", player->getPos().x, x_scroll, playerTileX, playerTileY, tileSizeYmult, player->getPos().y/tileSizeYmult);
#endif
    //    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
    //    {
    //        player->ceaseMovement();
    //    }
}

#endif // COLLISIONCONTROLLER_H
