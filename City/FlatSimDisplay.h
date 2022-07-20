#pragma once
#include <SFML\Graphics.hpp>

#include "Simulation.h"
#include "ScreenMap.h"

class FlatSimDisplay
{
    sf::Texture texture;
    sf::Sprite sprite;

    float lastTextureUpdate;
    float lastTime;

    Simulation simulation;
    void UpdateSimulationDisplay(ScreenMap& screenMap);

    void SetPixel(sf::Uint8* pixels, int x, int y, sf::Color color);
    void DrawLine(sf::Uint8* pixels, int x1, int y1, int x2, int y2, sf::Color color);
    void FillRect(sf::Uint8* pixels, int x, int y, int xs, int ys, sf::Color color);
public:
    FlatSimDisplay();
    void Update(float currentTime, ScreenMap& screenMap);
    void Render(sf::RenderWindow& window);
};

