#include <iostream>
#include "ScreenMap.h"

ScreenMap::ScreenMap() :
	offset(0.0f, 0.0f), scale(128.0f) // ~10x10 visible
{

}

sf::Vector2f ScreenMap::ScreenToMap(sf::Vector2f screenPos)
{
	sf::Vector2f windowSize(1600, 900); // TODO 
	sf::Vector2f centeredPos = screenPos - sf::Vector2f(0.5f, 0.5f);

	sf::Vector2f windowScaledPos = sf::Vector2f(
		centeredPos.x * windowSize.x,
		centeredPos.y * windowSize.y);
	return windowScaledPos * (1.0f / scale) + offset;
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