#include "collisioncontroller.h"

CollisionController::CollisionController()
{
}

void CollisionController::addCollideableSprite(SpriteController *s)
{
}

void CollisionController::addCollideablePlayer(PlayerController<double> *p)
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


void CollisionController::loadTileMap()
{

    s16 *bgMap = (s16 *)bgtool0.BgMap;
    map = new TileMapCell<double>*[bgtool0.height/tileSizeY];
    for ( int i = 0 ; i < bgtool0.height/tileSizeY ; i++ )
    {
        map[i] = new TileMapCell<double>[bgtool0.width/tileSizeX];
        for ( int j = 0 ; j < bgtool0.width/tileSizeX ; j++ )
        {
            //            map[i][j].pos.x = j*tileSizeX;
            //            map[i][j].pos.y = i*tileSizeY;
            //            map[i][j].xw = tileSizeX;
            //            map[i][j].yw = tileSizeY;
            //            asm volatile (
            //                    "mov r11, r11");
            map[i][j] = TileMapCell<double>((j+1)*tileSizeX, (i+1)*tileSizeY, tileSizeX, tileSizeY);
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

void CollisionController::checkForCollisions(const int& scroll)
{
    int playerTileX, playerTileY, playerTileY2;
    s16 *bgMap = (s16 *)bgtool0.BgMap;
    // TODO: Colisão com todos o bgmaps ou ao menos, com os delimitados pelo programador.

    playerTileX = ((int)player->getPos().x+scroll) / tileSizeX;
    playerTileY = player->getPos().y / tileSizeY;
    playerTileY2 = ((int)player->getPos().y -2*tileSizeY) / tileSizeY;

    //    AABB<double> pl = AABB<double>(Vector2<double>(player->pos.x, player->pos.y), tileSizeX, tileSizeY);
    //
    player->IntegrateVerlet();

    player->CollideVsTile(map[playerTileY][playerTileX]);
    if ( playerTileY+1 < 24 )
    player->CollideVsTile(map[playerTileY+1][playerTileX]);
    if ( playerTileY+2 < 24 )
    player->CollideVsTile(map[playerTileY+2][playerTileX]);

    player->CollideVsWorldBounds();
    //    Vector2<double> pos;
    //    pos = pl.getPos();
    //    player->pos.x = (float)pos.x;
    //    player->pos.y = (float)pos.y;


    //playerTileY2 = screenSizeY/tileSizeY;

    //playerTileX = 0;
    //playerTileY = 11;

    PA_OutputText(1, 1, 9,"Tile: %d      ", (int)bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]);
    PA_OutputText(1, 1, 10,"Tile: %d+%d %d %d      ", (int)player->getPos().x, scroll, playerTileX, playerTileY);
    //    if ( isCollideable(bgMap[playerTileX+playerTileY*bgtool0.width/tileSizeX]) )
    //    {
    //        player->ceaseMovement();
    //    }
}
