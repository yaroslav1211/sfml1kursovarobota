#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Background.h"
#include "Player.h"
#include "PlatformHolder.h"
#include "PhysicsEngine.h"

class GameWorld
{
public:
	GameWorld(sf::RenderWindow* window);
	~GameWorld();

	void blur();
	void unblur();

	void update(float DeltaTime);
	void draw();

private:
	sf::RenderWindow* m_window;

	Player m_player;
	Background m_background;
	PlatformHolder m_platformHolder;

	PhysicsEngine m_physicsEngine;

	bool m_blurred = false;
	sf::RectangleShape m_rectangle;
};