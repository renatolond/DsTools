// Include the application header
#include "scroll_engine.h"

// Entry point
int main(){
  PA_Init();

  cScrollEngine engine;
  engine.run();

  return 0;
}
