#include <PA_BgStruct.h>

extern const char teste_Tiles[];
extern const char teste_Map[];
extern const char teste_Pal[];

const PA_BgStruct teste = {
	PA_BgLarge,
	3392, 256,

	teste_Tiles,
	teste_Map,
	{teste_Pal},

	5312,
	{27136}
};
