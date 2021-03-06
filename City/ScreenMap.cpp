#include <iostream>
#include "ScreenMap.h"

ScreenMap::ScreenMap() :
	offset(0.0f, 0.0f), scale(64.0f), // ~10x10 visible
	currentMousePos(),
	leftClickPending(false), mapClickedPos(),
	queuedCommands()
{ }

sf::Vector2f ScreenMap::ScreenToMap(sf::Vector2f screenPos) { return screenPos * (1.0f / scale) + offset; }

sf::Vector2f ScreenMap::MapToScreen(sf::Vector2f mapPos) { return (mapPos - offset) * scale; }

sf::Vector2i ScreenMap::RoundToGrid(sf::Vector2f mapPos)
{
	int x = mapPos.x > 0 ? (int)mapPos.x : (int)mapPos.x - 1;
	int y = mapPos.y > 0 ? (int)mapPos.y : (int)mapPos.y - 1;
	return sf::Vector2i(x, y);
}

void ScreenMap::Translate(float x, float y) { offset += sf::Vector2f(x, y); }

void ScreenMap::Scale(float z) { scale *= z; }

void ScreenMap::UpdateMousePos(float x, float y) { currentMousePos = sf::Vector2f(x, y); }

void ScreenMap::LeftMouseClicked(float x, float y)
{
	mapClickedPos = ScreenMap::ScreenToMap(sf::Vector2f(x, y));
	leftClickPending = true;
}

bool ScreenMap::LeftClickPending()
{
	if (leftClickPending)
	{
		leftClickPending = false;
		return true;
	}

	return false;
}

sf::Vector2f ScreenMap::MapClickPos() { return mapClickedPos; }

void ScreenMap::SendGameCommand(sf::Keyboard::Key commandKey)
{
	queuedCommands.push(commandKey);
}

sf::Keyboard::Key ScreenMap::NextQueuedCommand()
{
	if (queuedCommands.empty())
	{
		return (sf::Keyboard::Key)0;
	}

	sf::Keyboard::Key key = queuedCommands.front();
	queuedCommands.pop();

	return key;
}

sf::Vector2f ScreenMap::MapMousePos()
{
	// Can't be done in UpdateMousePos because keyboard motion modifies offset/scale.
	return ScreenToMap(currentMousePos);
}

void ScreenMap::Log()
{
	std::cout << "Status: " << offset.x << "," << offset.y 
		<< ": " << scale << std::endl;

	sf::Vector2f min = ScreenToMap(sf::Vector2f(0.0f, 0.0f));
	sf::Vector2f max = ScreenToMap(sf::Vector2f(1.0f, 1.0f));
	std::cout << "Min/Max:" << min.x << "," << min.y << "||" <<
		max.x << "," << max.y << std::endl;

	std::cout << "Mouse: " << currentMousePos.x << ", " << currentMousePos.y << std::endl;
}