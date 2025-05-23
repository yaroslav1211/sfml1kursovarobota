#pragma once
#include "Player.h"
#include "PlatformHolder.h"

class PhysicsEngine
{
public:
	PhysicsEngine(Player* player, std::vector<Platform*>& platforms);

	void update(float dt);

private:
	Player* m_player;
	std::vector<Platform*>& m_platforms;
};