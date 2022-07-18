#pragma once
#include <SFML\System.hpp>

class ScreenMap
{
	sf::Vector2f offset;
	float scale;
public:
	ScreenMap();
	sf::Vector2f ScreenToMap(sf::Vector2f screenPos);
	void Translate(float x, float y);
	void Scale(float z);

	void Log();
};

