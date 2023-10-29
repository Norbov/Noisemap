#include "Noisemap.h"
#include "RandomNumber.h"

float multiplier = 0.1;

Noisemap::Noisemap() {
	noisemap = new float[width * height];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			noisemap[i * 256 + j] = (float)rand() / RAND_MAX;
		}
	}
}

Noisemap::Noisemap(int width, int height) {
	this->width = width;
	this->height = height;
	noisemap = new float[width * height];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			noisemap[i * height + j] = RandomNumberBetween0and1();
		}
	}
}

Noisemap::~Noisemap() {
	delete noisemap;
}

PerlinNoise::PerlinNoise(int width, int height) : Noisemap(width*12, height*12) {
	float* perlinNoisemap = new float[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float val = 0;

			float freq = 1;
			float amp = 1;

			for (int i = 0; i < 12; i++)
			{
				val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;

				freq *= 2;
				amp /= 2;
			}

			// Contrast
			val *= 1.2;

			// Clipping
			if (val > 1.0f)
				val = 1.0f;
			else if (val < -1.0f)
				val = -1.0f;

			perlinNoisemap[y * width + x] = val;
		}
	}
	delete noisemap;
	noisemap = perlinNoisemap;
}

PerlinNoise::PerlinNoise(int width, int height, int detail) : Noisemap(width * 12, height * 12) {
	this->detail = detail;
	float* perlinNoisemap = new float[width * height];
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			float val = 0;

			float freq = 1;
			float amp = 1;

			for (int i = 0; i < detail; i++)
			{
				val += perlin(x * freq / GRID_SIZE, y * freq / GRID_SIZE) * amp;

				freq *= 2;
				amp /= 2;
			}

			// Contrast
			val *= 1.2;

			// Clipping
			if (val > 1.0f)
				val = 1.0f;
			else if (val < -1.0f)
				val = -1.0f;

			perlinNoisemap[y * width + x] = val;
		}
	}
	delete noisemap;
	noisemap = perlinNoisemap;
}

float PerlinNoise::perlin(float x, float y) {
	// Determine grid cell corner coordinates
	int x0 = (int)x;
	int y0 = (int)y;

	int x1 = x0 + 1;
	int y1 = y0 + 1;

	// Compute Interpolation weights
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Compute and interpolate top two corners
	float n0 = dotGridGradient(x0, y0, x, y);
	float n1 = dotGridGradient(x1, y0, x, y);
	float ix0 = interpolate(n0, n1, sx);

	// Compute and interpolate bottom two corners
	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	float ix1 = interpolate(n0, n1, sx);

	// Final step: interpolate between the two previously interpolated values, now in y
	float value = interpolate(ix0, ix1, sy);

	return value;
}

float PerlinNoise::dotGridGradient(int ix, int iy, float x, float y) {

	float gradientX = sin(noisemap[iy * width + ix] * 3.14159265);
	float gradientY = cos(noisemap[iy * width + ix] * 3.14159265);

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * gradientX + dy * gradientY);
}

float PerlinNoise::interpolate(float a0, float a1, float w)
{
	return (a1 - a0) * (3.0 - w * 2.0) * w * w + a0;
}

TextureNoise::TextureNoise(int width, int height) : Noisemap(width, height) {
	this->width = width;
	this->height = height;
	float *texturemap;
	texturemap = new float[width * height];

	texturemap[0] = noisemap[0];
	for (int j = 1; j < width; j++)
	{
		texturemap[j] = NumberBettween0and1(noisemap[j - 1] + AddTextureNumber(noisemap[j], multiplier));
	}

	for (int i = 1; i < height; i++)
	{
		texturemap[i * height] = NumberBettween0and1(noisemap[(i - 1) * height] + AddTextureNumber(noisemap[i * height], multiplier));
		for (int j = 1; j < width; j++)
		{
			texturemap[i * height + j] = NumberBettween0and1((noisemap[i * height + j - 1] + noisemap[(i - 1) * height]) / 2 + AddTextureNumber(noisemap[i * height + j], multiplier));
		}
	}

	delete noisemap;
	noisemap = texturemap;
}
