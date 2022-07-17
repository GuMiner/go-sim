#include <iostream>
#include <sstream>
#include "FpsCounter.h"

FpsCounter::FpsCounter():
    lastTime(0.0f), timeTotal(0.1f), frameTotal(1)
{
    font = std::unique_ptr<sf::Font>(new sf::Font());
    if (!font->loadFromFile("media/fonts/DejaVuSans.ttf"))
    {
        std::cout << "ERROR: Could not load the font!" << std::endl;
    }

    fpsText = std::unique_ptr<sf::Text>(new sf::Text());
    fpsText->setFont(*font);
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