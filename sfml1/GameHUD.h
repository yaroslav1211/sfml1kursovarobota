#pragma once
#include <SFML/Graphics.hpp>

class GameHUD
{
public:
	GameHUD(sf::RenderWindow* window);

	void update(float dt);
	void draw();

private:
	sf::RenderWindow* m_window;

	sf::Text m_HeightMeterHUD;
	sf::Text m_shortcutsHelper;
};