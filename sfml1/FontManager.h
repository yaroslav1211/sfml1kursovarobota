#pragma once
#include <SFML/Graphics.hpp>

class FontManager
{
public:
	//Add other fonts if needed
	const sf::Font& getDefaultFont() const { return m_defaultFont; }

	static FontManager& getInstance()
	{
		static FontManager instance;
		return instance;
	}

private:
	FontManager() : m_defaultFont("resources/arial.ttf") {}

	sf::Font m_defaultFont;
};