//////////////////////////////////////////////////
// PAlib C++ project template                   //
// main.cpp                                     //
// Contains the entry point of the program.     //
//////////////////////////////////////////////////

// Include the application header
#include "ScrollEngine.h"

// Entry point
int main(){
	// Initialize PAlib
	PA_Init();

	// Run the application
	ScrollEngine engine;
	engine.run();

	return 0;
}
