//////////////////////////////////////////////////
// PAlib C++ project template                   //
// ScrollEngine.h                               //
// Main project header.                         //
//////////////////////////////////////////////////

#pragma once

// Include the PAlib header
#include <PA9.h>
#include <nds/ndstypes.h>

#include "constants.h"
#include "collisioncontroller.h"
#include "playercontroller.h"

// Include our graphics
#include "all_gfx.h"

// Using statements
//using PA::Application;
//using PA::Sprite;
using PA::Fixed;

#define SMALL_MARIO_ANIM_SPEED 10
#define HALFSCREEN ((256-16)/2)

// Main application class
class ScrollEngine: public PA::Application{
	// Put your variables here
	// Also don't forget to declare them
	// in the ScrollEngine.cpp file!
	static int nframe;
//	static PA::Sprite rocket;
        static PlayerController<double> smallMario;
        static CollisionController collisionController;

	// Main methods (needed by run())
	void init();
	void render();
	bool update();

	// Our own methods
        void loadGraphics();
};
