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
SpriteController ScrollEngine::smallMario(0, 1);
int SpriteCount;
/*u16 my_Map[4096];
u16 my_Map2[4096];*/
s32 scroll;
int greatest_bg;
int timer;
int oldTimer;

void timerFunction()
{
    timer++;
}

// Initialization function
void ScrollEngine::init(){
    TIMER_CR(1) = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
    TIMER_DATA(1) = TIMER_FREQ_1024(1000);
    irqSet(IRQ_TIMER1, timerFunction);
    irqEnable(IRQ_TIMER1);
    timer = oldTimer = 0;

    // Initialize the text system
    PA_InitText(1, 0);
    SpriteCount = 1;
    scroll = 0;
    // Load our graphics
    loadgraphics();

    //	// Set the rocket's starting position
    //	rocket.move(128, 192-64);
    //
    //	// Set the rocket's background priority
    //	rocket.priority(1); // on top of BG1 = below BG0 = below text background
    //
    //	Fixed a(4.5f);
    //	Fixed b(79);
    //	Fixed c(a);
    //	int d = 40;
    //
    //	PA_OutputText(1, 1, 10, "Arith1:    %d %d %f3", int(b + 1), int(b + c), float(a + 0.25f));
    //
    //	c = 45;
    //	c = (c * 2) - a;
    //	d *= Fixed(0.5f); // fake division
    //	PA_OutputText(1, 1, 11, "Arith2:    %d %d %f3", int(c), int(b * 2), float(b / 2));
    //	PA_OutputText(1, 1, 12, "Modulo:    %d %d", int(Fixed(4) % Fixed(2)), int(Fixed(414) % Fixed(141)));
    //	PA_OutputText(1, 1, 13, "FixedTest: %d %f3 %f3", int(a * 2), float(a * 0.5f), float(a / Fixed(2)));
    //	PA_OutputText(1, 1, 14, "Sqrt:      %d %f4", int(Fixed(25).sqrt()), float(Fixed(2).sqrt()));
    //	PA_OutputText(1, 1, 15, "Extra:     %d %d 0x%x %f3", 4 + Fixed(1.2f), d, a.raw(), float(Fixed::r2f(0x800)));
    //
    //	if(c == 85.5f) PA_OutputSimpleText(1, 1, 16, "CmpTest1:  true");
    //	if(c > a) PA_OutputSimpleText(1, 1, 17, "CmpTest2:  true");
}

// Graphics loading function
void ScrollEngine::loadgraphics(){
    // Load our rocket graphic
    //	PA_LoadSpritePal(1, 0, (void*) rocket_Pal);
    PA_LoadSpritePal(0, 1, (void*) small_mario_Pal);

    greatest_bg = bgtool0.width;

    PA_LoadBackground(0, 0, &bgtool0);
    PA_LoadBackground(0, 1, &bgtool1);
    PA_InitParallaxX(0, //screen
		     128, //Parallax speed for Background 0. 0 is no parallax (will scroll independently with PA_EasyBgScrollXY)
		     192, // Normal speed for Bg1
		     256, //   3/4 speed
		     0);

    //	rocket.create((void*)rocket_Sprite, OBJ_SIZE_32X32, 0);

    smallMario.create((void *)(small_mario_Sprite), OBJ_SIZE_16X16, 1);
    smallMario.move(0, 192-8*5);
    smallMario.priority(0);
    smallMario.addAnimation(1,2,SMALL_MARIO_ANIM_SPEED); // Walking
    smallMario.addAnimation(6,9,SMALL_MARIO_ANIM_SPEED); // Swimming
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
    PA_OutputText(1, 1, 4, "fTime: %d",(timer-oldTimer));
    //	PA_OutputText(1, 1, 3, "Y: %d"  , int(rocket.pos.y));
    //
    //        PA_OutputText(1, 1, 4, "Scroll: %03d", scroll);
    //
    // Render the rocket
    //	rocket.render();
    smallMario.render();
}

// Update function (if false, program exits)
bool ScrollEngine::update(){
    double fTime;
    fTime = (timer - oldTimer) / 1000.0;
    oldTimer = timer;

    // Increment the counter
    nframe ++;
    if ( Pad.Held.Right )
    {
	smallMario.hflip(0);
        smallMario.beginAnimation(0);
        scroll += 1 + fTime;
    }
    else if ( Pad.Held.Left )
    {
	smallMario.hflip(1);
        smallMario.beginAnimation(1);
        scroll -= 1 + fTime;
    }
    else
    {
	smallMario.stopAnimation();
    }
    if ( scroll < 0 ) scroll = 0;
    if ( scroll > greatest_bg - 256 ) scroll = greatest_bg - 256;
    // Move the rocket
    //    rocket.pos.x ++; if(rocket.pos.x == 256) rocket.pos.x = -64;
    //    rocket.pos.y --; if(rocket.pos.y == -64) rocket.pos.y = 192;
    PA_ParallaxScrollX(0, scroll);

    // Keep going
    return true;
}

// Optional cleanup function
// void ScrollEngine::cleanup()
//{
//}

