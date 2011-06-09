//////////////////////////////////////////////////
// PAlib C++ project template                   //
// main.cpp                                     //
// Contains the entry point of the program.     //
//////////////////////////////////////////////////

// Include the application header
#include "scroll-engine.h"
#include "global-data.h"

// Entry point
int main(){
	// Initialize PAlib
	PA_Init();

  sGlobalData global_data;

  global_data.miliseconds_between_game_cycles = 33;
  global_data.miliseconds_between_input_cycles = 50;

	// Run the application
  cScrollEngine engine;
  engine.set_global_data(&global_data);
	engine.run();

	return 0;
}
