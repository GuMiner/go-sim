#include <iostream>
#include <sstream>
#include "FpsCounter.h"
#include "FontManager.h"

FpsCounter::FpsCounter():
    lastTime(0.0f), timeTotal(0.1f), frameTotal(1)
{
    fpsText = std::unique_ptr<sf::Text>(new sf::Text());
    fpsText->setFont(*FontManager::Get()->Font());
    fpsText->setCharacterSize(24);
    fpsText->setFillColor(sf::Color::Green);
    fpsText->setString("FPS: ");
}

void FpsCounter::Update(float currentTime)
{
    ++frameTotal;
    timeTotal += (currentTime - lastTime);

    // Only update every half second
    if (timeTotal > 0.50f)
    {
        lastFrameRate = (float)frameTotal / (float)timeTotal;
        frameTotal = 0;
        timeTotal = 0.0f;

        std::stringstream fpsString;
        fpsString.precision(2);
        fpsString << "FPS: " << lastFrameRate;
        fpsText->setString(fpsString.str());
    }

    lastTime = currentTime;
}


void FpsCounter::Render(sf::RenderWindow* window)
{
    window->draw(*fpsText);
}