#include "Header.h"
#include "SFML/Graphics.hpp"

using namespace std;

int main() {
	float randomNumber = 0;
    int detail = 1;
    int mapTypeNumber;
    MapType mapType;
    cout << "Choose map type (Enter number) noisemap = 0, perlin noisemap = 1, texture noisemap = 2, rings = 3, ringIsland = 4 " << endl;
    cin >> mapTypeNumber;
    cout << "Enter seed " << endl;
    cin >> randomNumber;
    cout << "seed: " << randomNumber << endl;
    AddSeed(randomNumber);

    const int windowWidth = 800;
    const int windowHeight = 800;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "Perlin");

    sf::Uint8* pixels = new sf::Uint8[windowWidth * windowHeight * 4];

    switch (mapTypeNumber)
    {
    case 0:
        //Noisemap
        {
        Noisemap noisemap(windowWidth, windowHeight);

        for (int x = 0; x < windowWidth; x++)
        {
            for (int y = 0; y < windowHeight; y++)
            {
                int index = (y * windowWidth + x) * 4;

                int color = (int)(noisemap.noisemap[index / 4] * 255);

                // Set pixel color
                pixels[index] = color;
                pixels[index + 1] = color;
                pixels[index + 2] = color;
                pixels[index + 3] = 255;
            }
        }

        }
        break;
    case 1:
        //Perlin noise
        {
            cout << "Enter map detail between 1 and 12 " << endl;
            cin >> detail;
            int form;
            cout << "Normail = 0, Ink form = 1 " << endl;
            cin >> form;

            PerlinNoise perlinNoisemap(windowWidth, windowHeight, detail);

            for (int x = 0; x < windowWidth; x++)
            {
                for (int y = 0; y < windowHeight; y++)
                {
                    int index = (y * windowWidth + x) * 4;

                    int color;
                    if (form == 1) {
                        color = (int)(perlinNoisemap.noisemap[index / 4] * 255);
                    }
                    else {
                        // Convert 1 to -1 into 255 to 0
                        color = (int)(((perlinNoisemap.noisemap[index / 4] + 1.0f) * 0.5f) * 255);
                    }

                    // Set pixel color
                    pixels[index] = color;
                    pixels[index + 1] = color;
                    pixels[index + 2] = color;
                    pixels[index + 3] = 255;
                }
            }
        }
        break;
    case 2:
        //Test form
        {
            TextureNoise textureNoisemap(windowWidth, windowHeight);

            for (int x = 0; x < windowWidth; x++)
            {
                for (int y = 0; y < windowHeight; y++)
                {
                    int index = (y * windowWidth + x) * 4;

                    int color = (int)(textureNoisemap.noisemap[index / 64 / 4] * 255);

                    // Set pixel color
                    pixels[index] = color;
                    pixels[index + 1] = color;
                    pixels[index + 2] = color;
                    pixels[index + 3] = 255;
                }
            }
        }
        break;
    case 3:
        //Rings
        {
            cout << "Enter map detail between 1 and 12 " << endl;
            cin >> detail;
            int form;
            cout << "Normail = 0, Ink form = 1 " << endl;
            cin >> form;
            int ringCount;
            cout << "Ring Count " << endl;
            cin >> ringCount;

            PerlinNoise perlinNoisemap(windowWidth, windowHeight, detail);

            for (int x = 0; x < windowWidth; x++)
            {
                for (int y = 0; y < windowHeight; y++)
                {
                    int index = (y * windowWidth + x) * 4;

                    float height = -1;
                    for (int i = 0; i < ringCount; i++)
                    {
                        height += (2.0 / ringCount);

                        if (perlinNoisemap.noisemap[index / 4] <= height) {
                            perlinNoisemap.noisemap[index / 4] = (perlinNoisemap.noisemap[index / 4] - (i * 2 / ringCount) + 1) * ringCount;
                            break;
                        }
                    }

                    int color;
                    if (form == 1) {
                        color = (int)(perlinNoisemap.noisemap[index / 4] * 255);
                    }
                    else {
                        // Convert 1 to -1 into 255 to 0
                        color = (int)(((perlinNoisemap.noisemap[index / 4] + 1.0f) * 0.5f) * 255);
                    }

                    // Set pixel color
                    pixels[index] = color;
                    pixels[index + 1] = color;
                    pixels[index + 2] = color;
                    pixels[index + 3] = 255;
                }
            }
        }
        break;
    case 4:
        //Rings from half of the heights
        {
            cout << "Enter map detail between 1 and 12 " << endl;
            cin >> detail;
            int form;
            cout << "Normail = 0, Ink form = 1 " << endl;
            cin >> form;
            int ringCount;
            cout << "Ring Count " << endl;
            cin >> ringCount;

            PerlinNoise perlinNoisemap(windowWidth, windowHeight, detail);

            for (int x = 0; x < windowWidth; x++)
            {
                for (int y = 0; y < windowHeight; y++)
                {
                    int index = (y * windowWidth + x) * 4;

                    float height = 0;
                    for (int i = 0; i < ringCount; i++)
                    {
                        height += (1 / ringCount);

                        if (perlinNoisemap.noisemap[index / 4] <= height) {
                            perlinNoisemap.noisemap[index / 4] = (perlinNoisemap.noisemap[index / 4] - i / ringCount) * ringCount;
                            break;
                        }
                    }

                    int color;
                    if (form == 1) {
                        color = (int)(perlinNoisemap.noisemap[index / 4] * 255);
                    }
                    else {
                        // Convert 1 to -1 into 255 to 0
                        color = (int)(((perlinNoisemap.noisemap[index / 4] + 1.0f) * 0.5f) * 255);
                    }

                    // Set pixel color
                    pixels[index] = color;
                    pixels[index + 1] = color;
                    pixels[index + 2] = color;
                    pixels[index + 3] = 255;
                }
            }
        }
        break;
    default:
        cout << "Wrong map type " << endl;
        break;
    }

    sf::Texture texture;
    sf::Sprite sprite;

    texture.create(windowWidth, windowHeight);

    texture.update(pixels);

    delete pixels;

    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);

        window.display();
    }


	return 0;
}

