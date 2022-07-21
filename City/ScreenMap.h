#pragma once
#include <SFML\System.hpp>

class ScreenMap
{
	sf::Vector2f offset;
	float scale;

	sf::Vector2f currentMousePos;
public:
	ScreenMap();
	sf::Vector2f ScreenToMap(sf::Vector2f screenPos);
	sf::Vector2f MapToScreen(sf::Vector2f mapPos);
	void Translate(float x, float y);
	void Scale(float z);

	void UpdateMousePos(float x, float y);
	sf::Vector2f MapMousePos();

	void Log();
};

