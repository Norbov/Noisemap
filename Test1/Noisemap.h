typedef struct {
	float x, y;
} vector2;

class Noisemap {
	//vector<int> noisemap;
public:
	int width = 256;
	int height = 256;
	float* noisemap;

	Noisemap();
	Noisemap(int width, int height);
	~Noisemap();
};

class PerlinNoise : public Noisemap {
public:
	PerlinNoise();
	PerlinNoise(int width, int height);
	PerlinNoise(int width, int height, int detail);

	int detail;
private:
	const int GRID_SIZE = 400;

	float dotGridGradient(int ix, int iy, float x, float y);
	float interpolate(float a0, float a1, float w);
	float perlin(float x, float y);
};

class TextureNoise : public Noisemap {
public:
	TextureNoise();
	TextureNoise(int width, int height);
};