//////////////////////////////////////////////////
// PAlib C++ project template                   //
// ScrollEngine.cpp                             //
// Main project source code file.               //
//////////////////////////////////////////////////

// Include the application header
#include "ScrollEngine.h"

// Declare variables
int ScrollEngine::nframe = 0;
Sprite ScrollEngine::rocket(1, 0); // screen, sprite number
int SpriteCount;
u16 my_Map[4096];
u16 my_Map2[4096];
s32 scroll;

// Initialization function
void ScrollEngine::init(){
	// Initialize the text system
	PA_InitText(1, 0);
	SpriteCount = 1;
	// Load our graphics
	loadgraphics();

	// Set the rocket's starting position
	rocket.move(128, 192-64);

	// Set the rocket's background priority
	rocket.priority(1); // on top of BG1 = below BG0 = below text background

	Fixed a(4.5f);
	Fixed b(79);
	Fixed c(a);
	int d = 40;

	PA_OutputText(1, 1, 10, "Arith1:    %d %d %f3", int(b + 1), int(b + c), float(a + 0.25f));

	c = 45;
	c = (c * 2) - a;
	d *= Fixed(0.5f); // fake division
	PA_OutputText(1, 1, 11, "Arith2:    %d %d %f3", int(c), int(b * 2), float(b / 2));
	PA_OutputText(1, 1, 12, "Modulo:    %d %d", int(Fixed(4) % Fixed(2)), int(Fixed(414) % Fixed(141)));
	PA_OutputText(1, 1, 13, "FixedTest: %d %f3 %f3", int(a * 2), float(a * 0.5f), float(a / Fixed(2)));
	PA_OutputText(1, 1, 14, "Sqrt:      %d %f4", int(Fixed(25).sqrt()), float(Fixed(2).sqrt()));
	PA_OutputText(1, 1, 15, "Extra:     %d %d 0x%x %f3", 4 + Fixed(1.2f), d, a.raw(), float(Fixed::r2f(0x800)));

	if(c == 85.5f) PA_OutputSimpleText(1, 1, 16, "CmpTest1:  true");
	if(c > a) PA_OutputSimpleText(1, 1, 17, "CmpTest2:  true");
}

// Graphics loading function
void ScrollEngine::loadgraphics(){
	// Load our rocket graphic
	PA_LoadSpritePal(1, 0, (void*) rocket_Pal);
	//PA_LoadBg(0, 0, (void*)bg_1_Sprite, Blank, BG_256X256, 0,1);
	PA_BgStruct mybg = bg_1;
	for ( int i = 0; i <4096;i++) my_Map[i] = 18;
	for ( int i = 32 ; i < 64 ; i++ ) my_Map[i] = i-32;
	for ( int i = 32*21 ; i < 32*22 ; i++ ) my_Map[i] = (i%2)?4:3;
	for ( int i = 32*22 ; i < 32*23 ; i++ ) my_Map[i] = (i%2)?9:8;
	for ( int i = 32*23 ; i < 32*24 ; i++ ) my_Map[i] = (i%2)?4:3;
	my_Map[32*19 + 1] = 7;
	my_Map[32*19 + 2] = (4<<8)+7;

	my_Map[32*20 + 0] = 11;
	my_Map[32*20 + 1] = 1;
	my_Map[32*20 + 2] = 0;
	my_Map[32*20 + 3] = (4<<8)+11;
	mybg.BgMap=(void*)my_Map;
	PA_BgStruct mybg2 = bg_1;
	for ( int i = 0 ; i < 4096 ; i++ ) my_Map2[i] = 18;
	mybg2.BgMap=(void*)my_Map2;
	PA_LoadBackground(0, 3, &mybg2);
	PA_LoadBackground(0, 2, &mybg);
	PA_InitParallaxX(0, //screen
                128, //Parallax speed for Background 0. 0 is no parallax (will scroll independently with PA_EasyBgScrollXY)
				192, // Normal speed for Bg1
				256, //   3/4 speed
				0);
	//PA_LoadBackground(0, 3, &teste);
    //	PA_LoadBgPal(0,0,bg_1_Pal);
	//PA_LoadSpritePal(0, 1, (void*) bg_1_Pal);
	rocket.create((void*)rocket_Sprite, OBJ_SIZE_32X32, 0);


	// Rotate it
	rocket.bindrotset(0);
	rocket.dblsize(true);
	rocket.rotozoom(-64, 128, 128);
}

// Render function: called after each VBlank
void ScrollEngine::render(){
	// Output the value of our variable
	PA_OutputText(1, 1, 1, "Frame counter: %d", nframe);
	PA_OutputText(1, 1, 2, "X: %d  ", int(rocket.pos.x));
	PA_OutputText(1, 1, 3, "Y: %d"  , int(rocket.pos.y));

	// Render the rocket
	rocket.render();
}

// Update function (if false, program exits)
bool ScrollEngine::update(){
	// Increment the counter
	nframe ++;
    scroll ++;
	// Move the rocket
	rocket.pos.x ++; if(rocket.pos.x == 256) rocket.pos.x = -64;
	rocket.pos.y --; if(rocket.pos.y == -64) rocket.pos.y = 192;
	PA_ParallaxScrollX(0, scroll);

	// Keep going
	return true;
}

// Optional cleanup function
// void ScrollEngine::cleanup()
//{
//}

