#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class FontManager
{
	std::unique_ptr<sf::Font> font;
public:
	FontManager();
	static void Enable();

	static FontManager* Get();
	const sf::Font* Font();
};

