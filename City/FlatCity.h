#pragma once
#include <memory>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

#include "FpsCounter.h"
#include "FlatSimDisplay.h"

#include "ScreenMap.h"

class FlatCity
{
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<FpsCounter> fps;

	FlatSimDisplay simDisplay;
	ScreenMap screenMap;

	bool HandleEvents(bool alive);

	void Render(sf::Time elapsedTime);

public:
	FlatCity();
	void Setup();
	void Run();
	void Teardown();
};
