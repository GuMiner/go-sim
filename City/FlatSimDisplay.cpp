#include <iostream>
#include <sstream>
#include "FlatSimDisplay.h"
#include "FontManager.h"

int min(int x1, int x2)
{
	if (x1 < x2) return x1;
	return x2;
}

int max(int x1, int x2)
{
	if (x1 > x2) return x1;
	return x2;
}

FlatSimDisplay::FlatSimDisplay()
	:texture(), sprite(), lastTextureUpdate(0.0f), lastTime(0.0f),
	simulation()
{
}

void FlatSimDisplay::Setup()
{
	texture.create(1600, 900);
	texture.setRepeated(false);
	texture.setSmooth(false);

	sprite.setTexture(texture);

	cashBalance.setFont(*FontManager::Get()->Font());
	cashBalance.setCharacterSize(24);
	cashBalance.setFillColor(sf::Color::Green);
	cashBalance.setString("$: ");
	cashBalance.setPosition(sf::Vector2f(0, 40));
}

// This is for debugging, so this isn't the nicest algorithm out there.
void FlatSimDisplay::DrawLine(sf::Uint8* pixels, int x1, int y1, int x2, int y2, sf::Color color)
{
	int xDiff = abs(x1 - x2);
	int yDiff = abs(y1 - y2);

	if (xDiff > yDiff) // More horizontal than vertical
	{
		for (int i = 0; i <= xDiff; i++)
		{
			// Figure out relative y pos
			int yRelative = y1;
			if (xDiff != 0)
			{
				yRelative = y1 + ((y2 - y1) * i) / (xDiff);
			}
			
			if (x1 < x2)
			{
				SetPixel(pixels, x1 + i, yRelative, color);
			}
			else
			{
				SetPixel(pixels, x1 - i, yRelative, color);
			}
		}
	}
	else
	{
		for (int i = 0; i <= yDiff; i++)
		{
			// Figure out relative x pos
			int xRelative = x1;
			if (yDiff != 0)
			{
				xRelative = x1 + ((x2 - x1) * i) / (yDiff);
			}

			if (y1 < y2)
			{
				SetPixel(pixels, xRelative, y1 + i, color);
			}
			else
			{
				SetPixel(pixels, xRelative, y1 - i, color);
			}
		}
	}
}

void FlatSimDisplay::FillRect(sf::Uint8* pixels, int x, int y, int xs, int ys, sf::Color color)
{
	for (int i = 0; i < xs; i++)
	{
		for (int j = 0; j < ys; j++)
		{
			SetPixel(pixels, x + i, y + j, color);
		}
	}
}

void FlatSimDisplay::SetPixel(sf::Uint8* pixels, int x, int y, sf::Color color)
{
	if (x < 0 || y < 0 || x >= 1600 || y >= 900)
	{
		return;
	}

	pixels[(y * 1600 + x) * 4 + 0] = color.r;
	pixels[(y * 1600 + x) * 4 + 1] = color.g;
	pixels[(y * 1600 + x) * 4 + 2] = color.b;
	pixels[(y * 1600 + x) * 4 + 3] = color.a;
}

void FlatSimDisplay::UpdateSimulationDisplay(ScreenMap& screenMap)
{
	sf::Uint8* pixels = new sf::Uint8[1600 * 900 * 4]; // RGBA

	// Reset to black
	for (int i = 0; i < 1600; i++)
	{
		for (int j = 0; j < 900; j++)
		{
			SetPixel(pixels, i, j, sf::Color::Black);	
		}
	}

	// Draw game grid
	sf::Vector2f minGridVisible = screenMap.ScreenToMap(sf::Vector2f(0.0f, 0.0f));
	sf::Vector2f maxGridVisible = screenMap.ScreenToMap(sf::Vector2f(1600, 900));
	// std::cout << minGridVisible.x << " " << minGridVisible.y << ", " << maxGridVisible.x
	// 	<< " " << maxGridVisible.y << std::endl;
	for (int x = (int)minGridVisible.x; x < (int)maxGridVisible.x; x++)
	{
		for (int y = (int)minGridVisible.y; y < (int)maxGridVisible.y; y++)
		{
			GridCell& cell = simulation.GetGrid().Get(x, y);
			sf::Color color = sf::Color::Green;
			switch (cell.GetResource())
			{
			case Resource::Farmland:
				color = sf::Color(96, 64, 32); break; // Brown
			case Resource::Mineland:
				color = sf::Color(200, 200, 200); break; // Grey
			case Resource::Riverland:
				color = sf::Color::Blue; break;
			case Resource::Rockland:
				color = sf::Color(128, 128, 128); break; // Darker Grey
			case Resource::Sealand:
				color = sf::Color(128, 0, 200); break; // ?
			default:
				color = sf::Color::White; break;
			}

			sf::Vector2f ul = screenMap.MapToScreen(sf::Vector2f(x, y));
			sf::Vector2f lr = screenMap.MapToScreen(sf::Vector2f(x + 1, y + 1));

			FillRect(pixels, ul.x, ul.y, lr.x - ul.x, lr.y - ul.y, color);
		}
	}

	// Test cube
	// DrawLine(pixels, 100, 100, 100, 200, sf::Color::Green);
	// DrawLine(pixels, 100, 200, 200, 200, sf::Color::Green);
	// DrawLine(pixels, 100, 100, 200, 100, sf::Color::Green);
	// DrawLine(pixels, 200, 100, 200, 200, sf::Color::Green);
 
	// DrawLine(pixels, 100, 100, 200, 200, sf::Color::Green);
	// DrawLine(pixels, 200, 100, 100, 200, sf::Color::Green);

	// Current mouse selection
	sf::Vector2f mousePos = screenMap.MapMousePos();
	sf::Vector2f selectionMin = screenMap.MapToScreen(sf::Vector2f((int)mousePos.x, (int)mousePos.y));
	sf::Vector2f selectionMax = screenMap.MapToScreen(sf::Vector2f((int)(mousePos.x + 1), (int)(mousePos.y + 1)));
	DrawLine(pixels, selectionMin.x, selectionMin.y, selectionMax.x, selectionMin.y, sf::Color::Green);
	DrawLine(pixels, selectionMin.x, selectionMin.y, selectionMin.x, selectionMax.y, sf::Color::Green);
	DrawLine(pixels, selectionMax.x, selectionMin.y, selectionMax.x, selectionMax.y, sf::Color::Green);
	DrawLine(pixels, selectionMin.x, selectionMax.y, selectionMax.x, selectionMax.y, sf::Color::Green);

	texture.update(pixels);
	delete[] pixels;
}

void FlatSimDisplay::UpdateSimulationHUD()
{
	std::stringstream cashString;
	cashString << "$: " << simulation.GetTreasury().GetBalance();
	cashBalance.setString(cashString.str());
}

void FlatSimDisplay::Update(float currentTime, ScreenMap& screenMap)
{
	lastTextureUpdate += (currentTime - lastTime);
	if (lastTextureUpdate > sf::milliseconds(66).asSeconds())
	{
		// Avoid too frequent updates.
		UpdateSimulationDisplay(screenMap);
		UpdateSimulationHUD();

		lastTextureUpdate = 0.0f;
	}

	lastTime = currentTime;
}

void FlatSimDisplay::Render(sf::RenderWindow& window)
{
	window.draw(sprite);
	window.draw(cashBalance);
}