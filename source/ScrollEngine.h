//////////////////////////////////////////////////
// PAlib C++ project template                   //
// ScrollEngine.h                               //
// Main project header.                         //
//////////////////////////////////////////////////

#pragma once

// Include the PAlib header
#include <PA9.h>
#include <nds/ndstypes.h>

// Include our graphics
#include "all_gfx.h"

// Using statements
using PA::Application;
using PA::Sprite;
using PA::Fixed;

// Main application class
class ScrollEngine: public Application{
	// Put your variables here
	// Also don't forget to declare them
	// in the ScrollEngine.cpp file!
	static int nframe;
	static Sprite rocket;
	static Sprite smallMario;

	// Main methods (needed by run())
	void init();
	void render();
	bool update();

	// Our own methods
	void loadgraphics();
};
