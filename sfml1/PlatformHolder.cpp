#include "PlatformHolder.h"
#include "GameConfig.h"
#include "Player.h"
#include "DistanceTracker.h"

PlatformHolder::PlatformHolder(sf::RenderWindow* window, Player* player) : GameObject(window), m_player(player)
{
	m_platforms.push_back(new Platform{ window, {100, 200} });
	m_platforms.push_back(new Platform{ window, {400, 800} });
	m_platforms.push_back(new Platform{ window, {600, 500} });
	m_platforms.push_back(new Platform{ window, {700, 100} });
	m_platforms.push_back(new Platform{ window, {1200, 700} });
	m_platforms.push_back(new Platform{ window, {1500, 400} });
	m_platforms.push_back(new Platform{ window, {200, 300} });
	m_platforms.push_back(new Platform{ window, {1700, 700} });
	m_platforms.push_back(new Platform{ window, {1100, 500} });
	m_platforms.push_back(new Platform{ window, {1100, 200} });
	m_platforms.push_back(new Platform{ window, {900, 250} });

	//Floor
	m_platforms.push_back(new Platform{ window, {0, 1050}, 1920 });
}

void PlatformHolder::update(float dt)
{
	for (Platform* platform : m_platforms)
	{
		platform->update(dt);
	}

	movePlatforms(dt);
	clearInvisiblePlatforms();
	generatePlatforms(dt);
}

void PlatformHolder::draw()
{
	for (Platform* platform : m_platforms)
	{
		platform->draw();
	}
}

void PlatformHolder::generatePlatforms(float dt)
{
	//setting it to true right after the last platform was generated
	if (m_generateNewPlatform)
	{
		//Just to add some small help for the player
		//Can decrease with time to make the gameplay more challenging
		constexpr float GenerateEpsilon = 200.0f;

		//v_final^2 = v_start^2 + 2 * a * height
		//as long as final velocity is 0 ->
		// 2 * a * heigh = v_start^2
		//-> height = v_start^2 / 2a
		const float playerMaxJumpHeight = std::abs(GameConfig::JumpImpulse) * std::abs(GameConfig::JumpImpulse)
			/ (2.0f * GameConfig::GravityAcceleration);

		// + Platforms movement speed to compensate the fact the platforms are moving as well
		const float maxReachableHeight = playerMaxJumpHeight
			+ std::abs(GameConfig::PlatformsMovementSpeed - -GameConfig::PlatformHeight);

		//Player height is not needed after all
		m_nextGenerationHeight = std::rand() % static_cast<int>(
			maxReachableHeight - GenerateEpsilon);

		m_generateNewPlatform = false;
	}

	if (Platform* lastPlatform = m_platforms.back())
	{
		if (lastPlatform->getPosition().y > m_nextGenerationHeight)
		{
			const float x = std::max(0, static_cast<int>(std::rand() % m_window->getSize().x - GameConfig::PlatformWidth));
			m_platforms.push_back(new Platform{ m_window, {x, 0} });
			m_generateNewPlatform = true;
		}
	}
}

void PlatformHolder::movePlatforms(float dt)
{
	for (Platform* platform : m_platforms)
	{
		platform->move({ 0, GameConfig::PlatformsMovementSpeed * dt });
	}

	DistanceTracker::addPlatformDistance(GameConfig::PlatformsMovementSpeed * dt);
}

void PlatformHolder::clearInvisiblePlatforms()
{
	//HMMM, crashes for some reasons
	//remove_if -> delete objects -> erase


	//c++20
	//std::erase_if(m_platforms,
	//	[window = this->m_window](Platform* platform)
	//	{
	//		return platform->getPosition().y > window->getSize().y; 
	//	}
	//);
}