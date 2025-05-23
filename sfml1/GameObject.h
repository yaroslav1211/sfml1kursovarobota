#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
	GameObject(sf::RenderWindow* window) : m_window(window) {}

	virtual void update(float dt) = 0;
	virtual void draw() = 0;

	virtual sf::FloatRect getBoundingBox() const { return {}; }

	virtual void onCollision(GameObject* gameObject) {}


	virtual ~GameObject() {}

protected:
	sf::RenderWindow* m_window;
};