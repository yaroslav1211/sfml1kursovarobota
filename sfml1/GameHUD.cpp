#include "GameHUD.h"
#include "FontManager.h"
#include "DistanceTracker.h"

GameHUD::GameHUD(sf::RenderWindow* window)
	: m_window(window)
	, m_HeightMeterHUD(FontManager::getInstance().getDefaultFont())
	, m_shortcutsHelper(FontManager::getInstance().getDefaultFont())
{
	m_HeightMeterHUD.setCharacterSize(48);
	m_HeightMeterHUD.setFillColor(sf::Color::Black);

	m_HeightMeterHUD.setPosition({ 20.0f, 20.0f });

	m_shortcutsHelper.setCharacterSize(48);
	m_shortcutsHelper.setFillColor(sf::Color::Black);
	m_shortcutsHelper.setPosition({ 20.0f, m_window->getSize().y - 100.0f });
	m_shortcutsHelper.setString("P - pause/unpause\nEsc - exit game");
}

void GameHUD::update(float dt)
{
	const float distance = DistanceTracker::getPlayerHeight();

	// /10 -> Let's make it less dynamic, so user can track its value more easily
	m_HeightMeterHUD.setString(std::to_string(static_cast<int>(distance / 10)) + " m");
}

void GameHUD::draw()
{
	m_window->draw(m_HeightMeterHUD);
	m_window->draw(m_shortcutsHelper);
}