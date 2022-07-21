#pragma once
#include <memory>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class FpsCounter
{
    float lastTime;
    float lastFrameRate;

    float timeTotal;
    int frameTotal;

    std::unique_ptr<sf::Text> fpsText;

public:
    FpsCounter();
    void Update(float currentTime);
    void Render(sf::RenderWindow* window);
};

