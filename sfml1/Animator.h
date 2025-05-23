#pragma once
#include <SFML/Graphics.hpp>

struct AnimationSettings
{
	const int FrameWidth;
	const int FrameHeight;
	const int FramesCount;

	const float AnimationSpeed;

	const char* textureFileName;
};

class Animator
{
public:
	Animator(AnimationSettings animationSettings);

	void update(float dt);
	void reset();

	sf::Sprite& getSprite() { return m_sprite; }

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Clock m_animationClock;
	int m_currentFrame = 0;

	AnimationSettings m_animationSettings;
};