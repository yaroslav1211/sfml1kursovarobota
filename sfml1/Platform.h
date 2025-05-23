#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "GameConfig.h"

class Platform : public GameObject
{
public:
	Platform(sf::RenderWindow* window, const sf::Vector2f& position, float width = GameConfig::PlatformWidth);
	void setPosition(const sf::Vector2f& position) { m_shapeObject.setPosition(position); }
	sf::Vector2f getPosition() const { return m_shapeObject.getPosition(); }

	void update(float dt) override {}
	void draw() override { m_window->draw(m_shapeObject); }

	void move(sf::Vector2f delta) { setPosition(getPosition() + delta); }

	sf::FloatRect getBoundingBox() const override { return m_shapeObject.getGlobalBounds(); }

private:
	sf::RectangleShape m_shapeObject;
};