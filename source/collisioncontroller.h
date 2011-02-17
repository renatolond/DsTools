#ifndef COLLISIONCONTROLLER_H
#define COLLISIONCONTROLLER_H

#include <PA9.h>

#include "all_gfx.h"
#include "spritecontroller.h"
#include "tilemapcell.h"
#include "playercontroller.h"

template <class T>
class CollisionController
{
    PlayerController<T> *player;
    TileMapCell<T> **map;
public:
    CollisionController();
    void checkForCollisions(const int &scroll);
    void addCollideableSprite(SpriteController *s);
    void addCollideablePlayer(PlayerController<T> *p);
//    bool isCollideable(s16 tile);
    void loadTileMap();
};

template <class T>
CollisionController<T>::CollisionController()
{
}

template <class T>
void CollisionController<T>::addCollideableSprite(SpriteController *s)
{
}

template <class T>
void CollisionController<T>::addCollideablePlayer(PlayerController<T> *p)
{
    player = p;
}

// 18 e 19 tem que ter colisão
// bom pra testar :)

//template <class T>
//bool CollisionController<T>::isCollideable(s16 tile)
//{
//    PA_OutputText(1, 1, 9,"Tile: %d      ", (int)tile);
//    if ( tile == 18 || tile == 19 || tile == 25 || tile == 26 )
//        return true;
//    else
//        return false;
//}


template <class T>
void CollisionController<T>::loadTileMap()
{

    s16 *bgMap = (s16 *)bgtool0.BgMap;
    map = new TileMapCell<T>*[bgtool0.height/tileSizeY];
    for ( int i = 0 ; i < bgtool0.height/tileSizeY ; i++ )
    {
        map[i] = new TileMapCell<T>[bgtool0.width/tileSizeX];
        for ( int j = 0 ; j < bgtool0.width/tileSizeX ; j++ )
        {
            //            map[i][j].pos.x = j*tileSizeX;
            //            map[i][j].pos.y = i*tileSizeY;
            //            map[i][j].xw = tileSizeX;
            //            map[i][j].yw = tileSizeY;
            //            asm volatile (
            //                    "mov r11, r11");
            map[i][j] = TileMapCell<T>((j+1)*tileSizeXmult, (i+1)*tileSizeYmult, tileSizeXmult, tileSizeYmult);
            //            asm volatile (
            //                    "mov r11, r11");
            int index = j+i*(bgtool0.width/tileSizeX);
            if ( bgMap[index] == 60 || bgMap[index] == 61 || bgMap[index] == 62 || bgMap[index] == 63 ) // PLACEHOLDER!
            {
                map[i][j].SetState(TileEnum::full);
            }
            else
                map[i][j].SetState(TileEnum::empty);
        }
    }
    //                asm volatile (
    //                        "mov r11, r11");
}

template <class T>
void CollisionController<T>::checkForCollisions(const int& scroll)
{
    int playerTileX, playerTileY;//, playerTileY2;
    s16 *bgMap = (s16 *)bgtool0.BgMap;
    // TODO: Colisão com todos o bgmaps ou ao menos, com os delimitados pelo programador.

    playerTileX = player->getPos().x / tileSizeXmult;
    asm("mov r11,r11");
    playerTileY = player->getPos().y / tileSizeYmult;
    asm("mov r11,r11");
    PA_OutputText(1, 1, 12,"x: %d y: %d     ", player->getPos().x, player->getPos().y);
    //playerTileY2 = ((int)player->getPos().y -2*tileSizeY) / tileSizeY;

    //    AABB<double> pl = AABB<double>(Vector2<double>(player->pos.x, player->pos.y), tileSizeX, tileSizeY);
    //

//    for ( int i = playerTileX ; i < playerTileX+2 ; i++ )
//    for ( int j = playerTileY ; j < playerTileY+2 ; j++ )
//            if ( i >= 0 && i < 32 && j >= 0 && j < 24 )
//                player->CollideVsTile(map[j][i]);

//    player->CollideVsTile(map[playerTileY][playerTileX]);
//    if ( playerTileY+1 < 24 )
//    player->CollideVsTile(map[playerTileY+1][playerTileX]);
//    if ( playerTileY+2 < 24 )
//    player->CollideVsTile(map[playerTileY+2][playerTileX]);

    player->CollideVsWorldBounds();
    //    Vector2<double> pos;
    //    pos = pl.getPos();
    //    player->pos.x = (float)pos.x;
    //    player->pos.y = (float)pos.y;


    //playerTileY2 = screenSizeY/tileSizeY;

    //playerTileX = 0;
    //playerTileY = 11;

    PA_OutputText(1, 1, 9,"Tile: %d      ", bgMap[(int)playerTileX+playerTileY*bgtool0.width/tileSizeX]);
    PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d %d %d     ", player->getPos().y, scroll, playerTileX, playerTileY, tileSizeYmult, player->getPos().y/tileSizeYmult);
    //    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
    //    {
    //        player->ceaseMovement();
    //    }
}

#endif // COLLISIONCONTROLLER_H
