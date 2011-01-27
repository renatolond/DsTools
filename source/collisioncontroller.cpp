#include "collisioncontroller.h"

CollisionController::CollisionController()
{
}

void CollisionController::addCollideableSprite(SpriteController *s)
{
}

void CollisionController::addCollideablePlayer(PlayerController *p)
{
    player = p;
}

// 18 e 19 tem que ter colisão
// bom pra testar :)

bool CollisionController::isCollideable(s16 tile)
{
    PA_OutputText(1, 1, 9,"Tile: %d      ", (int)tile);
    if ( tile == 18 || tile == 19 || tile == 25 || tile == 26 )
        return true;
    else
        return false;
}


void CollisionController::checkForCollisions(const int& scroll)
{
    int playerTileX, playerTileY, playerTileY2;
    s16 *bgMap = (s16 *)bgtool0.BgMap;
    // TODO: Colisão com todos o bgmaps ou ao menos, com os delimitados pelo programador.

    playerTileX = ((int)player->pos.x+scroll) / tileSizeX;
    playerTileY = (int)player->pos.y / tileSizeY;
    playerTileY2 = ((int)player->pos.y -2*tileSizeY) / tileSizeY;

    PA_Draw16bitRect(0, player->pos.x, player->pos.y, player->pos.x+player->sizeX, player->pos.y+player->sizeY, 0);

    //playerTileY2 = screenSizeY/tileSizeY;

    //playerTileX = 0;
    //playerTileY = 11;

    PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d      ", (int)player->pos.x, scroll, playerTileX, playerTileY);
    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
    {
        player->ceaseMovement();
    }
}
