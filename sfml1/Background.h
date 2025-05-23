#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

class Background : public GameObject
{
public:
	Background(sf::RenderWindow* window);

	void update(float dt) override {}
	void draw() override;

private:

	sf::Texture m_texture;
	sf::Sprite m_sprite;
};