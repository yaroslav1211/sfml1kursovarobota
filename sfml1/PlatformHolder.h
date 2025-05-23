#pragma once
#include "GameObject.h"
#include "Platform.h"
#include <vector>

class PlatformHolder : public GameObject
{
public:
	PlatformHolder(sf::RenderWindow* window, class Player* player);

	void update(float dt) override;
	void draw() override;

	std::vector<Platform*>& getPlatforms() { return m_platforms; }

private:
	void generatePlatforms(float dt);

	void movePlatforms(float dt);
	void clearInvisiblePlatforms();

	std::vector<Platform*> m_platforms;

	float m_nextGenerationHeight = 0.0f;
	bool m_generateNewPlatform = true;

	class Player* m_player;
};