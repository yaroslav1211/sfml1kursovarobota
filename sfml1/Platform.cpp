#include "Platform.h"
#include "GameConfig.h"

Platform::Platform(sf::RenderWindow* window, const sf::Vector2f& position, float width)
	: GameObject(window), m_shapeObject{ { width, GameConfig::PlatformHeight} }
{
	const sf::Color DarkGreen{ 0, 150, 0 };

	m_shapeObject.setPosition(position);
	m_shapeObject.setFillColor(DarkGreen);
}