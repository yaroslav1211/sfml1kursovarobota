#pragma once

class DistanceTracker
{
public:
	static DistanceTracker& getInstance()
	{
		static DistanceTracker instance;
		return instance;
	}

	static void addPlatformDistance(float delta) { getInstance().m_platformsDistanceMoved += delta; }
	static void setPlayerHeightOnScreen(float height) { getInstance().m_playerHeightOnScreen = height; }

	static float getPlatformDistance() { return getInstance().m_platformsDistanceMoved; }
	static float getPlayerHeight() { return getInstance().m_playerHeightOnScreen + getInstance().m_platformsDistanceMoved; }

private:
	float m_platformsDistanceMoved = 0.0f;
	float m_playerHeightOnScreen = 0.0f;
};