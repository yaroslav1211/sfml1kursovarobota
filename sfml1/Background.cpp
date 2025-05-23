#include "Background.h"

Background::Background(sf::RenderWindow* window) : GameObject(window), m_texture("resources/background.png"), m_sprite(m_texture)
{
	m_texture.setRepeated(true);
	m_sprite.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(m_window->getSize().x), static_cast<int>(m_window->getSize().y) }));
}

void Background::draw()
{
	m_window->draw(m_sprite);
}