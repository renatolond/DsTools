////////////////////////////
// PAlib project template //
////////////////////////////

// Lines starting with two slashes are ignored by the compiler
// Basically you can use them to comment what are you doing
// In fact, this kind of lines are called comments :P

// Include PAlib so that you can use it
#include <PA9.h>
#include "vectorrenderer.h"
#include "tilemapcell.h"
#include "aabb.h"

class myApp : public PA::Application
{
       VectorRenderer<int> vr;
       AABB<int> aabb;
       void init();
    void render();
    bool update();
};

void myApp::init()
{
    PA_Init();
    PA_InitText(1, 0);
    PA_InitText(0, 0);

    vr = VectorRenderer<int>();
    aabb = AABB<int>(Vector2<int>((screenMinX+screenSizeX)/2, 10), 10, 10);
    aabb.vr = &vr;
    vr.SetStyle(1, 0xFF0000, 0xFFFFFF, 0x1);
    vr.Clear();
}

bool myApp::update()
{
    vr.Clear();

    PA_OutputText(0, 0, 20, "Teste");

    if ( Pad.Newpress.A || Pad.Held.Down )
    aabb.IntegrateVerlet();

    aabb.CollideVsWorldBounds();

    if ( Stylus.Newpress )
    {
        Vector2<int> oldPos, pos;
        oldPos = aabb.getPos();
        pos = Vector2<int>(Stylus.X, Stylus.Y);
        oldPos = pos - oldPos;
//        oldPos.normalize();
//        oldPos = pos - oldPos;

        aabb.setOldPos(oldPos);
        aabb.setPos(pos);
    }

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

    vr.Clear();
    //PA_Draw16bitRect(0, 0, 0, 100, 100, 0x801F);

    //vList.push_back(k); vList.push_back(l); vList.push_back(m);
    //vr.DrawArc(l, n, m);
    //vr.DrawConcaveCCWArc(m, l);
    //vr.DrawLine(m.x, m.y, l.x, l.y);
    //vr.DrawLine(m.x-(m.y-l.y), m.y, m.x, m.y);
    //TileMapCell<int> t(1,2,3,4);
    //AABB<int> aabb();

    aabb.Draw();

    PA_16bitSwapBuffer(0);
//    PA_Draw16bitRect(0, 0, 0, 100, 100, 0x801F);
}

int main(){
    myApp my;
    my.run();
    return 0;
}
