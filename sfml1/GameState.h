#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "GameWorld.h"

class GameStateManager;

class GameState
{
public:
	GameState(GameStateManager& context, sf::RenderWindow* window) : m_gameStateManager(context), m_window(window) {}

	virtual void onEnter() {} //To add initialization during state enter
	virtual void onExit() {} //To add deinitialization during state exit

	virtual void updateState() = 0;
	virtual void update(float DeltaTime) = 0;
	virtual void draw() = 0;

protected:
	sf::RenderWindow* m_window;
	GameStateManager& m_gameStateManager;
};

class GameState_Playing : public GameState
{
public:
	GameState_Playing(GameStateManager& context, GameWorld* gameWorld, sf::RenderWindow* window) : GameState(context, m_window), m_GameWorld(gameWorld) {}

	void onEnter() override;

	void updateState() override;
	void update(float DeltaTime) override;
	void draw() override;

private:
	GameWorld* m_GameWorld;

	bool m_pressedLastFrame = true;
};

class GameState_Pause : public GameState
{
public:
	GameState_Pause(GameStateManager& context, GameWorld* gameWorld, sf::RenderWindow* window);

	void updateState() override;
	void update(float DeltaTime) override;
	void draw() override;

	void onEnter() override;
	void onExit() override;

private:
	GameWorld* m_GameWorld;

	bool m_pressedLastFrame = true;

	sf::Text m_pauseText;
	sf::Clock m_textLoopClock;
	bool m_isVisible = true;
};

class GameState_TitleScreen : public GameState
{
public:
	GameState_TitleScreen(GameStateManager& context, sf::RenderWindow* window);

	void onEnter() override;
	void onExit() override;

	void updateState() override;
	void update(float DeltaTime) override;
	void draw() override;

private:
	sf::Text m_text;

	sf::Texture m_startTexture;
	sf::Sprite m_startSprite;
};