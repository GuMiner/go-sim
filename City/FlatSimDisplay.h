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

public:
    FlatSimDisplay();
    void Update(float currentTime, ScreenMap& screenMap);
    void Render(sf::RenderWindow& window);
};

