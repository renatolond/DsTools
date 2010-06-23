#include <PA_BgStruct.h>

extern const char bg_Tiles[];
extern const char bg_Map[];
extern const char bg_Pal[];

const PA_BgStruct bg = {
	PA_BgLarge,
	3392, 256,

	bg_Tiles,
	bg_Map,
	{bg_Pal},

	5312,
	{27136}
};
