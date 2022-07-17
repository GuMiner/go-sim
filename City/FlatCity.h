#pragma once
#include <memory>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "FpsCounter.h"
#include "FlatSimDisplay.h"

class FlatCity
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<FpsCounter> fps;

	FlatSimDisplay simDisplay;

	// Handles GUI-based events, such as closing the application, resizing the window, etc.
	bool HandleEvents(bool alive);

	// Renders the scene.
	void Render(sf::Time elapsedTime);

public:
	FlatCity();
	void Setup();
	void Run();
	void Teardown();
};
