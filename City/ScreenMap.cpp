#include <iostream>
#include "ScreenMap.h"

ScreenMap::ScreenMap() :
	offset(0.0f, 0.0f), scale(64.0f) // ~10x10 visible
{

}

sf::Vector2f ScreenMap::ScreenToMap(sf::Vector2f screenPos)
{
	return screenPos * (1.0f / scale) + offset;
}

sf::Vector2f ScreenMap::MapToScreen(sf::Vector2f mapPos)
{
	return (mapPos - offset) * scale;
}


void ScreenMap::Translate(float x, float y)
{
	offset += sf::Vector2f(x, y);
}

void ScreenMap::Scale(float z)
{
	scale *= z;
}

void ScreenMap::Log()
{
	std::cout << "Status: " << offset.x << "," << offset.y 
		<< ": " << scale << std::endl;

	sf::Vector2f min = ScreenToMap(sf::Vector2f(0.0f, 0.0f));
	sf::Vector2f max = ScreenToMap(sf::Vector2f(1.0f, 1.0f));
	std::cout << "Min/Max:" << min.x << "," << min.y << "||" <<
		max.x << "," << max.y << std::endl;
}