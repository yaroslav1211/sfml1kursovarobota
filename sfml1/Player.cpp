#pragma optimize("", off)

#include "Player.h"
#include "Platform.h"
#include "GameConfig.h"
#include "SoundManager.h"

AnimationSettings PlayerAnimationSettings = { 100, 121, 7 , 0.1f, "resources/animated_jump.png" };

Player::Player(sf::RenderWindow* window) : GameObject(window), m_texture("resources/doodle.png"), m_sprite(m_texture)
, m_animator(PlayerAnimationSettings)
{
	getSpriteImpl().setOrigin({ getSpriteImpl().getLocalBounds().size.x / 2.0f, getSpriteImpl().getLocalBounds().size.y / 2.0f });

	getSpriteImpl().setScale({ 1.2f, 1.2f });

	const sf::Vector2u windowSize = m_window->getSize();

	getSpriteImpl().setPosition(sf::Vector2f{ windowSize.x / 2.0f,
		getSpriteImpl().getGlobalBounds().size.y });

	m_position = getSpriteImpl().getPosition();

	m_orientation = PlayerOrientation::Right;

	m_cooldownTimer.restart();
	m_cooldownSec = 0.3f;
}

void Player::update(float dt)
{
	handleInput(dt);
	physicsUpdate(dt);
	orientationUpdate();

	//The m_position is being modified in handleInput and in physicsUpdate parts
	getSpriteImpl().setPosition(m_position);

	m_isOnGround = false;

	DistanceTracker::setPlayerHeightOnScreen(m_window->getSize().y - m_position.y);

	m_animator.update(dt);
}

void Player::draw()
{
	m_window->draw(getSpriteImpl());
}

sf::FloatRect Player::getBoundingBox() const
{
	return getSpriteImpl().getGlobalBounds();
}

void Player::onCollision(GameObject* collidedObject)
{
	if (Platform* platform = dynamic_cast<Platform*>(collidedObject))
	{
		if (m_velocity.y >= 0.0f)
		{
			m_velocity.y = 0.0f;
			m_isOnGround = true;

			m_animator.reset();
		}
	}
	//Let's assume for now, that only Platform's are collidable
}

void Player::handleInput(float dt)
{
	const float SPEED_X = 800.0f * dt;

	float deltaX = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		deltaX += -SPEED_X;
		m_newOrientationRequest = PlayerOrientation::Left;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		deltaX += SPEED_X;
		m_newOrientationRequest = PlayerOrientation::Right;
	}

	m_position.x += deltaX;
}

void Player::physicsUpdate(float dt)
{
	updateGravity(dt);
	updateJump(dt);

	applyVelocity(dt);
}

void Player::orientationUpdate()
{
	if (m_newOrientationRequest != m_orientation)
	{
		getSpriteImpl().setScale({ getSpriteImpl().getScale().x * -1.0f, getSpriteImpl().getScale().y });
		m_orientation = m_newOrientationRequest;
	}
}

sf::Sprite& Player::getSpriteImpl()
{
	bool useAnimation = true;
	if (useAnimation)
	{
		return m_animator.getSprite();
	}

	return m_sprite;
}

const sf::Sprite& Player::getSpriteImpl() const
{
	return const_cast<Player*>(this)->getSpriteImpl();
}

void Player::updateGravity(float dt)
{
	const float MaxSpeed = 900.0f;


	if (!m_isOnGround)
	{
		m_velocity.y += GameConfig::GravityAcceleration * dt;
		if (m_velocity.y >= MaxSpeed)
		{
			m_velocity.y = MaxSpeed;
		}
	}
}

void Player::updateJump(float dt)
{
	if (!m_isOnGround)
	{
		return;
	}

	const bool shouldJump = GameConfig::AutoJump ||
		(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_cooldownTimer.getElapsedTime().asSeconds() > m_cooldownSec);

	if (shouldJump)
	{
		m_cooldownTimer.restart();
		jumpImpl(dt);

		SoundManager::getInstance().playJump();
	}
}

void Player::jumpImpl(float dt)
{
	m_velocity.y = GameConfig::JumpImpulse;
}

void Player::applyVelocity(float dt)
{
	const sf::Vector2f displacement{ m_velocity.x * dt, m_velocity.y * dt };
	m_position += displacement;
}