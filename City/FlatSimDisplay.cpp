#include "FlatSimDisplay.h"

FlatSimDisplay::FlatSimDisplay()
	:texture(), sprite(), lastTextureUpdate(0.0f), lastTime(0.0f),
	simulation()
{
	texture.create(1600, 900);
	texture.setRepeated(false);
	texture.setSmooth(false);

	sprite.setTexture(texture);
}

void FlatSimDisplay::UpdateSimulationDisplay(ScreenMap& screenMap)
{
	sf::Uint8* pixels = new sf::Uint8[1600 * 900 * 4]; // RGBA

	// Reset to black
	for (int i = 0; i < 1600; i++)
	{
		for (int j = 0; j < 900; j++)
		{
			pixels[(j * 1600 + i) * 4 + 0] = 0;
			pixels[(j * 1600 + i) * 4 + 1] = 0;
			pixels[(j * 1600 + i) * 4 + 2] = 0;
			pixels[(j * 1600 + i) * 4 + 3] = 255;
		}
	}

	// Draw game grid
	sf::Vector2f minGridVisible = screenMap.ScreenToMap(sf::Vector2f(0.0f, 0.0f));
	sf::Vector2f maxGridVisible = screenMap.ScreenToMap(sf::Vector2f(1.0f, 1.0f));
	
	// TODO finish this later.
	// Iterate visible regions
	// Draw these as hashed on the map
	// Avoid drawing outside the display.

	texture.update(pixels);
	delete[] pixels;
}

void FlatSimDisplay::Update(float currentTime, ScreenMap& screenMap)
{
	lastTextureUpdate += (currentTime - lastTime);
	if (lastTextureUpdate > sf::milliseconds(66).asSeconds())
	{
		// Avoid too frequent updates.
		UpdateSimulationDisplay(ScreenMap & screenMap);
		lastTextureUpdate = 0.0f;
	}

	lastTime = currentTime;
}

void FlatSimDisplay::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}