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
            map[i][j] = TileMapCell<T>(j*tileSizeXmult+(T)(tileSizeXmult/2), i*tileSizeYmult+(T)(tileSizeYmult/2), (T)(tileSizeXmult/2), (T)(tileSizeYmult/2));
            //            asm volatile (
            //                    "mov r11, r11");
            int index = j+i*(bgtool0.width/tileSizeX);
            if (bgMap[index] == 60 || bgMap[index] == 61 || bgMap[index] == 62 || bgMap[index] == 63 ||
                bgMap[index] == 19 || bgMap[index] == 20 || bgMap[index] == 25 || bgMap[index] == 26) // PLACEHOLDER!
            {
                //                char message[1024];
                //                sprintf(message, "x:%d y:%d", j,i);
                //                nocashMessage(message);
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
        inline void collideVsTile(TileMapCell<T> **map, PlayerController<T> *player, int j, int i)
{
    if ( i >= 0 && i < worldMaxX/tileSizeXmult && j >= 0 && j < worldMaxY/tileSizeYmult )
        player->CollideVsTile(map[j][i]);
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

//    collideVsTile(map, player, playerTileY+1, playerTileX-1);
    collideVsTile(map, player, playerTileY+1, playerTileX);
//    collideVsTile(map, player, playerTileY+1, playerTileX+1);
    collideVsTile(map, player, playerTileY, playerTileX-1);
    collideVsTile(map, player, playerTileY, playerTileX);
    collideVsTile(map, player, playerTileY, playerTileX+1);
    collideVsTile(map, player, playerTileY-1, playerTileX-1);
    collideVsTile(map, player, playerTileY-1, playerTileX);
    collideVsTile(map, player, playerTileY-1, playerTileX+1);

//    for ( int i = playerTileX-1 ; i <= playerTileX+1 ; i++ )
//        for ( int j = playerTileY+1 ; j >= playerTileY-1 ; j-- )
//            if ( i >= 0 && i < worldMaxX/tileSizeXmult && j >= 0 && j < worldMaxY/tileSizeYmult )
//                player->CollideVsTile(map[j][i]);

    player->CollideVsWorldBounds();


    PA_OutputText(1, 1, 9,"Tile: %d      ", bgMap[(int)playerTileX+playerTileY*bgtool0.width/tileSizeX]);
    PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d %d %d     ", player->getPos().x, scroll, playerTileX, playerTileY, tileSizeYmult, player->getPos().y/tileSizeYmult);
    //    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
    //    {
    //        player->ceaseMovement();
    //    }
}

#endif // COLLISIONCONTROLLER_H
