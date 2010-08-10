#include <PA_BgStruct.h>

extern const char bgtool_Tiles[];
extern const char bgtool_Map[];
extern const char bgtool_Pal[];

const PA_BgStruct bgtool = {
  PA_BgLarge,
  3392, 192,

bgtool_Tiles,
bgtool_Map,
{bgtool_Pal},

4096,
{20352}
};
