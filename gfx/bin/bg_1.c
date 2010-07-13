#include <PA_BgStruct.h>

extern const char bg_1_Tiles[];
extern const char bg_1_Map[];
extern const char bg_1_Pal[];

const PA_BgStruct bg_1 = {
	PA_BgNormal,
	256, 192,

	bg_1_Tiles,
	bg_1_Map,
	{bg_1_Pal},

	2880,
	{1536}
};
