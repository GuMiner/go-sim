#pragma once
#include <SFML\Graphics.hpp>

#include "Simulation.h"

class FlatSimDisplay
{
    sf::Texture texture;
    sf::Sprite sprite;

    float lastTextureUpdate;
    float lastTime;

    Simulation simulation;
    void UpdateSimulationDisplay();

public:
    FlatSimDisplay();
    void Update(float currentTime);
    void Render(sf::RenderWindow& window);
};

