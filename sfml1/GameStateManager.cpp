#include "GameStateManager.h"
#include "GameState.h"

GameStateManager::GameStateManager(GameWorld* gameWorld, GameStateId initialGameStateId, sf::RenderWindow* window)
{
	m_gameStates[static_cast<std::size_t>(GameStateId::TitleScreen)] = new GameState_TitleScreen(*this, window);
	m_gameStates[static_cast<std::size_t>(GameStateId::Pause)] = new GameState_Pause(*this, gameWorld, window);
	m_gameStates[static_cast<std::size_t>(GameStateId::Playing)] = new GameState_Playing(*this, gameWorld, window);

	m_currentGameState = m_gameStates[static_cast<std::size_t>(initialGameStateId)];
	m_currentGameState->onEnter();
}

void GameStateManager::setGameState(GameStateId newGameState)
{
	m_currentGameState->onExit();
	m_currentGameState = m_gameStates[static_cast<std::size_t>(newGameState)];
	m_currentGameState->onEnter();
}

GameStateManager::~GameStateManager()
{
	for (int i = 0; i < static_cast<unsigned int>(GameStateId::Count); i++)
	{
		delete m_gameStates[i];
	}
}