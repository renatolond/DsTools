////////////////////////////
// PAlib project template //
////////////////////////////

// Lines starting with two slashes are ignored by the compiler
// Basically you can use them to comment what are you doing
// In fact, this kind of lines are called comments :P

// Include PAlib so that you can use it
#include <PA9.h>
#include "all_gfx.h"
#include "vectorrenderer.h"
#include "tilemapcell.h"
#include "aabb.h"

class myApp : public PA::Application
{
//       VectorRenderer<int> vr;
       AABB<int> aabb;
       TileMapCell<int> demoTile;
       void init();
    void render();
    bool update();
};

void myApp::init()
{
    PA_Init();
    PA_InitText(1, 0);

    PA_LoadBackground(0, 1, &bg_blank);

//    vr = VectorRenderer<int>();
    aabb = AABB<int>(Vector2<int>((screenMinX+screenSizeX)/2, 2), 8, 8);
    demoTile = TileMapCell<int>((screenMinX+screenMaxX)/2, (screenMinY+screenMaxY)/2, tileSizeX, tileSizeY);
    demoTile.SetState(TileEnum::full);
//    aabb.vr = &vr;
//    vr.SetStyle(1, 0xFF0000, 0xFFFFFF, 0x1);
//    vr.Clear();
}

bool myApp::update()
{
//    vr.Clear();

    PA_OutputText(1, 0, 20, "X %d Y %d", aabb.getPos().x, aabb.getPos().y);

    if ( Pad.Newpress.A || Pad.Held.L )
    aabb.IntegrateVerlet();

    if ( Stylus.Held )
    {
        Vector2<int> pos;//oldPos,
        pos = Vector2<int>(Stylus.X, Stylus.Y);

        aabb.setPos(pos);
    }
    else if ( Pad.Held.Up || Pad.Held.Down || Pad.Held.Left || Pad.Held.Right )
    {

        Vector2<int> pos, oldPos, v, newPos, f;
        int objspeed = 4;
        int maxspeed = 20;

        f.x = f.y = 0;
        if ( Pad.Held.Up )
            f.y -= (objspeed - gravity);
        else if ( Pad.Held.Down )
            f.y += objspeed;
        if ( Pad.Held.Left )
            f.x -= objspeed;
        else if ( Pad.Held.Right )
            f.x += objspeed;

        oldPos = aabb.getPos();
        pos = aabb.getPos();
        v = pos - oldPos;

        newPos = v + f;
        if ( newPos.y < -maxspeed ) newPos.y = -maxspeed;
        if ( newPos.x < -maxspeed ) newPos.x = -maxspeed;
        if ( newPos.x > maxspeed ) newPos.x = maxspeed;
        if ( newPos.y > maxspeed ) newPos.y = maxspeed;

        aabb.setPos(newPos+oldPos);
    }

    aabb.CollideVsTile(demoTile);
    aabb.CollideVsWorldBounds();

    return true;
}

void myApp::render()
{


    Vector2<int> k, l, m, n;
//    k = Vector2<int>(2,3);
    l = Vector2<int>(100, 45);
    m = Vector2<int>(100, 75);
    n = Vector2<int>(130, 75);
//
//    std::vector< Vector2<int> > vList;

//    vr.Clear();
    //PA_Draw16bitRect(0, 0, 0, 100, 100, 0x801F);

    //vList.push_back(k); vList.push_back(l); vList.push_back(m);
    //vr.DrawArc(l, n, m);
    //vr.DrawConcaveCCWArc(m, l);
    //vr.DrawLine(m.x, m.y, l.x, l.y);
    //vr.DrawLine(m.x-(m.y-l.y), m.y, m.x, m.y);
    //TileMapCell<int> t(1,2,3,4);
    //AABB<int> aabb();

    aabb.Draw();
    demoTile.Draw();

//    PA_16bitSwapBuffer(0);
//    PA_Draw16bitRect(0, 0, 0, 100, 100, 0x801F);
}

int main(){
    myApp my;
    my.run();
    return 0;
}
