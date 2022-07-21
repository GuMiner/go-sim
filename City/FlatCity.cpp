#include <iostream>
#include "FlatCity.h"
#include "FontManager.h"

FlatCity::FlatCity()
    : simDisplay(),
      screenMap()
{
}


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
            switch (event.key.code)
            {
            case sf::Keyboard::Escape:
                alive = false;
                break;
            case sf::Keyboard::Left:
                screenMap.Translate(-1.0f, 0.0f);
                break;
            case sf::Keyboard::Right:
                screenMap.Translate(1.0f, 0.0f);
                break;
            case sf::Keyboard::Up:
                screenMap.Translate(0.0f, 1.0f);
                break;
            case sf::Keyboard::Down:
                screenMap.Translate(0.0f, -1.0f);
                break;
            case sf::Keyboard::Add:
                screenMap.Scale(2.0f);
                break;
            case sf::Keyboard::Subtract:
                screenMap.Scale(0.5f);
                break;
            default:
                break;
            }

            screenMap.Log();
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            screenMap.UpdateMousePos(event.mouseMove.x, event.mouseMove.y);
        }
    }

    return alive;
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

    // Font
    FontManager::Enable();

    // FPS
    fps = std::unique_ptr<FpsCounter>(new FpsCounter());

    simDisplay.Setup();
}

void FlatCity::Render(sf::Time elapsedTime)
{
    window->clear(sf::Color::Black);
    
    simDisplay.Update(elapsedTime.asSeconds(), screenMap);
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