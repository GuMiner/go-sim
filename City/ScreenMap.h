#pragma once
#include <queue>
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class ScreenMap
{
	sf::Vector2f offset;
	float scale;

	sf::Vector2f currentMousePos;

	bool leftClickPending;
	sf::Vector2f mapClickedPos;

	std::queue<sf::Keyboard::Key> queuedCommands;
public:
	ScreenMap();
	sf::Vector2f ScreenToMap(sf::Vector2f screenPos);
	sf::Vector2f MapToScreen(sf::Vector2f mapPos);
	sf::Vector2i RoundToGrid(sf::Vector2f mapPos);
	void Translate(float x, float y);
	void Scale(float z);

	void UpdateMousePos(float x, float y);
	void LeftMouseClicked(float x, float y);
	sf::Vector2f MapMousePos();
	bool LeftClickPending();
	sf::Vector2f MapClickPos();

	void SendGameCommand(sf::Keyboard::Key commandKey);
	sf::Keyboard::Key NextQueuedCommand();

	void Log();
};

