#include <iostream>
#include <vector>

#include "RandomNumber.h"
#include "Noisemap.h"

void AddSeed(int seed);

enum MapType
{
	noisemap,
	perlinNoisemap,
	textureNoisemap
};
