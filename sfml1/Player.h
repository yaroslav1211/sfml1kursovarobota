#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "DistanceTracker.h"
#include "Animator.h"

enum class PlayerOrientation
{
	Left,
	Right,
	Center
};


class Player : public GameObject
{
public:
	Player(sf::RenderWindow* window);

	void update(float dt) override;
	void draw() override;
	sf::FloatRect getBoundingBox() const override;
	void onCollision(GameObject* collidedObject);

private:
	void handleInput(float dt);
	void physicsUpdate(float dt);
	void orientationUpdate();

	sf::Sprite& getSpriteImpl();
	const sf::Sprite& getSpriteImpl() const;

	//The order is important
	//Here's why: //https://wiki.sei.cmu.edu/confluence/display/cplusplus/OOP53-CPP.+Write+constructor+member+initializers+in+the+canonical+order
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	PlayerOrientation m_orientation;
	PlayerOrientation m_newOrientationRequest;

	//Physics Impl part. Make it its own class
private:
	void updateGravity(float dt);

	void updateJump(float dt);
	void jumpImpl(float dt);

	void applyVelocity(float dt);

private:
	sf::Vector2f m_velocity;

	sf::Clock m_cooldownTimer;
	float m_cooldownSec = 1.0f;

	bool m_isOnGround = false;

private:
	Animator m_animator;
};