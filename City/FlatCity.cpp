#include <iostream>
#include "FlatCity.h"

// Handles GUI-based events, such as closing the application, resizing the window, etc.
bool FlatCity::HandleEvents(bool alive)
{
    // Handle all events.
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            alive = false;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code   == sf::Keyboard::Escape)
            {
                alive = false;
            }
        }
    }

    return alive;
}

FlatCity::FlatCity()
    : simDisplay()
{

}

void FlatCity::Setup()
{
    std::cout << "Setting up FlatCity..." << std::endl;

    // Main window
    // 24 depth bits, 8 stencil bits, 8x AA, major version 4.
    sf::ContextSettings contextSettings = sf::ContextSettings(24, 8, 8, 4, 0);

    sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
    window = std::unique_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1600, 900), "FlatCity", style, contextSettings));
    window->setFramerateLimit(60);
    window->setPosition(sf::Vector2i(100, 10));

    // FPS
    fps = std::unique_ptr<FpsCounter>(new FpsCounter());
}

void FlatCity::Render(sf::Time elapsedTime)
{
    window->clear(sf::Color::Black);
    
    simDisplay.Update(elapsedTime.asSeconds());
    simDisplay.Render(*window.get());

    fps->Update(elapsedTime.asSeconds());
    fps->Render(window.get());
}

void FlatCity::Run()
{
    std::cout << "Running FlatCity..." << std::endl;

    bool alive = true;
    sf::Clock timer;
    while (alive)
    {
        alive = HandleEvents(alive);
        Render(timer.getElapsedTime());
        window->display();
    }
}

void FlatCity::Teardown()
{
    std::cout << "Cleaning up FlatCity..." << std::endl;
}