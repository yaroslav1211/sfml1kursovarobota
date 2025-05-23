#include "GameState.h"
#include "Boundaries.h"
#include "GameStateManager.h"
#include "FontManager.h"
#include "SoundManager.h"

void GameState_Playing::onEnter()
{
	SoundManager::getInstance().playInGameMusic();
}

void GameState_Playing::updateState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		if (!m_pressedLastFrame)
		{
			m_pressedLastFrame = true;
			m_gameStateManager.setGameState(GameStateId::Pause);
		}
	}
	else
	{
		m_pressedLastFrame = false;
	}
}

void GameState_Playing::update(float DeltaTime)
{
	m_GameWorld->update(DeltaTime);
}

void GameState_Playing::draw()
{
	m_GameWorld->draw();
}

GameState_Pause::GameState_Pause(GameStateManager& context, GameWorld* gameWorld, sf::RenderWindow* window)
	: GameState(context, window), m_GameWorld(gameWorld), m_pauseText(FontManager::getInstance().getDefaultFont())
{
	m_pauseText.setCharacterSize(240);
	m_pauseText.setFillColor(sf::Color::Blue);
	m_pauseText.setString("PAUSED");
	m_pauseText.setRotation(sf::degrees(45));

	m_pauseText.setPosition({ m_window->getSize().x / 2.0f - m_pauseText.getGlobalBounds().size.x / 2.0f
		, m_window->getSize().y / 2.0f - m_pauseText.getGlobalBounds().size.y / 2.0f });
}

void GameState_Pause::updateState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		if (!m_pressedLastFrame)
		{
			m_pressedLastFrame = true;
			m_gameStateManager.setGameState(GameStateId::Playing);
		}
	}
	else
	{
		m_pressedLastFrame = false;
	}
}

void GameState_Pause::update(float DeltaTime)
{
	//Don't update GameWorld, just skipping gameWorld update makes the world freeze in Paused Mode
	constexpr unsigned int BlinkPeriod = 500;

	bool needUpdate = false;

	if (m_textLoopClock.getElapsedTime().asMilliseconds() > BlinkPeriod)
	{
		m_textLoopClock.restart();
		m_isVisible = !m_isVisible;
		needUpdate = true;
	}

	if (needUpdate)
	{
		sf::Color color = m_pauseText.getFillColor();
		color.a = (m_isVisible) ? 255 : 0;
		m_pauseText.setFillColor(color);
	}
}

void GameState_Pause::draw()
{
	m_GameWorld->draw();
	m_window->draw(m_pauseText);
}

void GameState_Pause::onEnter()
{
	m_isVisible = true;
	m_textLoopClock.restart();
	m_GameWorld->blur();

	SoundManager::getInstance().playPause();
}

void GameState_Pause::onExit()
{
	m_GameWorld->unblur();

	SoundManager::getInstance().playUnpause();
}

GameState_TitleScreen::GameState_TitleScreen(GameStateManager& context, sf::RenderWindow* window)
	: GameState(context, window), m_startTexture("resources/title_screen.jpg"), m_startSprite(m_startTexture), m_text(FontManager::getInstance().getDefaultFont())
{
	m_text.setCharacterSize(100); // in pixels, not points!
	m_text.setFillColor(sf::Color::Cyan);
	m_text.setString("PRESS ENTER TO START THE GAME!");
	m_text.setOrigin({ m_text.getGlobalBounds().size.x / 2, m_text.getGlobalBounds().size.y / 2 });
	m_text.setPosition({ m_window->getSize().x / 2.0f, m_window->getSize().y / 2.0f });
}

void GameState_TitleScreen::onEnter()
{
	SoundManager::getInstance().playTitleMusic();
}

void GameState_TitleScreen::onExit()
{
	SoundManager::getInstance().stopTitleMusic();
}

void GameState_TitleScreen::updateState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		m_gameStateManager.setGameState(GameStateId::Playing);
	}
}

void GameState_TitleScreen::update(float DeltaTime)
{

}

void GameState_TitleScreen::draw()
{
	m_window->clear(sf::Color::White);

	m_window->draw(m_startSprite);
	m_window->draw(m_text);
}