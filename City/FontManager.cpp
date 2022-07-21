#include <iostream>
#include "FontManager.h"

std::unique_ptr<FontManager> globalFontManager(nullptr);

FontManager::FontManager()
{
	font = std::unique_ptr<sf::Font>(new sf::Font());
	if (!font->loadFromFile("media/fonts/DejaVuSans.ttf"))
	{
		std::cout << "ERROR: Could not load the font!" << std::endl;
	}
}

void FontManager::Enable()
{
	globalFontManager = std::unique_ptr<FontManager>(new FontManager());
}

FontManager* FontManager::Get()
{
	return globalFontManager.get();
}

const sf::Font* FontManager::Font()
{
	return font.get();
}