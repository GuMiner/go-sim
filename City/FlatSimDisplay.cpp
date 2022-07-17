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

void FlatSimDisplay::UpdateSimulationDisplay()
{
	sf::Uint8* pixels = new sf::Uint8[1600 * 900 * 4]; // RGBA
	for (int i = 0; i < 1600; i++)
	{
		for (int j = 0; j < 900; j++)
		{
			pixels[(j * 1600 + i) * 4 + 0] = rand() % 256;
			pixels[(j * 1600 + i) * 4 + 1] = rand() % 256;
			pixels[(j * 1600 + i) * 4 + 2] = rand() % 256;
			pixels[(j * 1600 + i) * 4 + 3] = rand() % 256;
		}
	}

	texture.update(pixels);
	delete[] pixels;
}

void FlatSimDisplay::Update(float currentTime)
{
	lastTextureUpdate += (currentTime - lastTime);
	if (lastTextureUpdate > sf::milliseconds(66).asSeconds())
	{
		// Avoid too frequent updates.
		UpdateSimulationDisplay();
		lastTextureUpdate = 0.0f;
	}

	lastTime = currentTime;
}

void FlatSimDisplay::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
}