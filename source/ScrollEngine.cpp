//////////////////////////////////////////////////
// PAlib C++ project template                   //
// ScrollEngine.cpp                             //
// Main project source code file.               //
//////////////////////////////////////////////////

// Include the application header
#include "ScrollEngine.h"

// Declare variables
int ScrollEngine::nframe = 0;
//PA::Sprite ScrollEngine::rocket(1, 0); // screen, sprite number
PlayerController<myint> ScrollEngine::smallMario(Vector2<myint>(0, 0), tileSizeX, tileSizeY, 0, 1);
CollisionController<myint> ScrollEngine::collisionController;
int SpriteCount;
/*u16 my_Map[4096];
u16 my_Map2[4096];*/
double scroll;
int greatest_bg;
int timer;
int oldTimer;
int moveTimer;
int gameTimer;

void timerFunction()
{
    timer++;
}

// Initialization function
void ScrollEngine::init(){
    // Initialize the text system
    PA_InitText(1, 0);
    SpriteCount = 1;
    scroll = 0;
    // Load our graphics
    loadGraphics();

    TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA(1) = TIMER_FREQ_1024(1000);
    irqSet(IRQ_TIMER1, timerFunction);
    irqEnable(IRQ_TIMER1);
    timer = oldTimer = 0;
}

// Graphics loading function
void ScrollEngine::loadGraphics(){
    // Load our rocket graphic
    //	PA_LoadSpritePal(1, 0, (void*) rocket_Pal);
    PA_LoadSpritePal(0, 1, (void*) small_mario_Pal);

    greatest_bg = bgtool0.width;


    PA_LoadBackground(0, 0, &bgtool0);
    //PA_LoadBackground(0, 1, &bgtool1);
    PA_InitParallaxX(0, //screen
                     screenSizeX, //Parallax speed for Background 0. 0 is no parallax (will scroll independently with PA_EasyBgScrollXY)
                     screenSizeX, // Normal speed for Bg1
		     256, //   3/4 speed
		     0);

    //	rocket.create((void*)rocket_Sprite, OBJ_SIZE_32X32, 0);

    smallMario.spr.create((void *)(small_mario_Sprite), OBJ_SIZE_16X16, 1);
    smallMario.spr.move(0, screenSizeY-(tileSizeY/100)*5);
    smallMario.spr.priority(0);
    smallMario.spr.addAnimation(1,3,SMALL_MARIO_ANIM_SPEED); // Walking
    smallMario.spr.addAnimation(4,4,0); // Drag
    smallMario.spr.addAnimation(5,5,0); // Jumping
    smallMario.spr.addAnimation(6,9,SMALL_MARIO_ANIM_SPEED); // Swimming

    collisionController.addCollideablePlayer(&smallMario);
    collisionController.loadTileMap();

    //smallMario.startanim(0, 3, 5);
    //PA::Sprite::


    //	// Rotate it
    //	rocket.bindrotset(0);
    //	rocket.dblsize(true);
    //	rocket.rotozoom(-64, 128, 128);
}

// Render function: called after each VBlank
void ScrollEngine::render(){
    // Output the value of our variable
    PA_OutputText(1, 1, 1, "Frame counter: %d", nframe);
    PA_OutputText(1, 1, 2, "Miliseconds: %d  ", timer);
    PA_OutputText(1, 1, 3, "fTime: %d",(timer-oldTimer));
    //	PA_OutputText(1, 1, 3, "Y: %d"  , int(rocket.pos.y));
    //
    //        PA_OutputText(1, 1, 4, "Scroll: %03d", scroll);
    //
    // Render the rocket
    //	rocket.render();
    char message[1024];
    sprintf(message,"pos: x %ld y %ld",smallMario.getPos().x, smallMario.getPos().y);
    PA_OutputText(1,1,4, "%s", message);
    sprintf(message,"oldP   os: x %ld y %ld",smallMario.getOldPos().x, smallMario.getOldPos().y);
    PA_OutputText(1,1,5, "%s", message);
    smallMario.Draw();
}

// Update function (if false, program exits)
bool ScrollEngine::update(){
    double fTime;
    fTime = (timer - oldTimer) / 1000.0;
    oldTimer = timer;

    // Increment the counter
    nframe ++;

    PA_OutputText(1, 1, 11,"Ready?");
    if ( timer - moveTimer > milisecondsBetweenInputCycles )
    {
        moveTimer = timer;

//        if ( Pad.Held.A )
//            smallMario.isRunning(true);
//        else
//            smallMario.isRunning(false);
//
        if ( Pad.Held.Right )
        {
            smallMario.accelerateRight();
        }
        else if ( Pad.Held.Left )
        {
            smallMario.accelerateLeft();
        }
//        else
//        {
////            smallMario.applyFriction();
//        }
//
//        if ( Pad.Held.Up )
//        {
//            smallMario.accelerateUp(timer);
//        }

//        smallMario.applyGravity();
    }
    smallMario.IntegrateVerlet();
    collisionController.checkForCollisions(scroll);
    if ( timer - gameTimer > milisecondsBetweenGameCycles )
    {
        gameTimer = timer;

        int horzSpeed;
        if ( horzSpeed > 0 && !smallMario.isCenteredOnScreen() )
            horzSpeed = smallMario.centerOnScreen();
        //double horzSpeed;
        //horzSpeed = smallMario.getHorizontalSpeed();
        //if ( horzSpeed > 0 && !smallMario.isCenteredOnScreen() )
         //   horzSpeed = smallMario.centerOnScreen();
//        else if ( horzSpeed < 0 )
//            horzSpeed = smallMario.uncenterOnScreen(horzSpeed, scroll);

        scroll += horzSpeed;
//        Vector2<double> p, op;
//        p = smallMario.getPos();
//        op = smallMario.getOldPos();
//        double speed = p.x - op.x;
//        double xw, yw;
//        smallMario.getExt(xw, yw);
//
//        p.x = ((screenMaxX-screenMinX)/2 - xw*2);
//        op.x = p.x - speed;
//        smallMario.setPos(p);
//        smallMario.setOldPos(op);

//        int vertSpeed = smallMario.getVerticalSpeed(timer);
//        PA_OutputText(1, 1, 5, "vertSpeed: %d       ",vertSpeed);

//        smallMario.pos.y = smallMario.pos.y + vertSpeed;
    }


    if ( scroll < 0 ) scroll = 0;
    if ( scroll > greatest_bg - screenSizeX ) scroll = greatest_bg - screenSizeX;

    PA_ParallaxScrollX(0, scroll);

    // Keep going
    return true;
}

// Optional cleanup function
// void ScrollEngine::cleanup()
//{
//}

