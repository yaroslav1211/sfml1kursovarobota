#include "Animator.h"

Animator::Animator(AnimationSettings settings) : m_animationSettings(settings), m_texture(settings.textureFileName), m_sprite(m_texture)
{
	m_sprite.setTextureRect(sf::IntRect{ {0, 0},	//position
			{m_animationSettings.FrameWidth, m_animationSettings.FrameHeight} });	//size
}

void Animator::update(float dt)
{
	if (m_animationClock.getElapsedTime().asSeconds() > m_animationSettings.AnimationSpeed)
	{
		m_currentFrame = (m_currentFrame + 1) % m_animationSettings.FramesCount;

		m_sprite.setTextureRect(sf::IntRect{ {m_currentFrame * m_animationSettings.FrameWidth, 0},	//position
			{m_animationSettings.FrameWidth, m_animationSettings.FrameHeight} });	//size

		m_animationClock.restart();
	}
}

void Animator::reset()
{
	m_currentFrame = 0;
	m_animationClock.restart();

	m_sprite.setTextureRect(sf::IntRect{ {m_animationSettings.FrameWidth, 0},	//position
			{m_animationSettings.FrameWidth, m_animationSettings.FrameHeight} });	//size
}