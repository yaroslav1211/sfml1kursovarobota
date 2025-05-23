#pragma once
#include "SFML/Audio.hpp"

class SoundManager
{
public:
	void playDamage() { m_collisionSound.play(); }
	void playJump() { m_jumpSound.play(); }

	void playInGameMusic() { m_inGameMusic.play(); }
	void pauseInGameMusic() { m_inGameMusic.pause(); }

	void playTitleMusic() { m_titleMusic.play(); }
	void stopTitleMusic() { m_titleMusic.stop(); }

	void playPause() { m_pauseSound.play(); }
	void playUnpause() { m_unpauseSound.play(); }

	static SoundManager& getInstance()
	{
		static SoundManager instance;
		return instance;
	}

private:
	SoundManager()
		: m_damageBuffer("resources/damage.wav")
		, m_jumpBuffer("resources/jump.wav")
		, m_collisionSound(m_damageBuffer)
		, m_jumpSound(m_jumpBuffer)
		, m_inGameMusic("resources/background_music.ogg")
		, m_titleMusic("resources/title_music.ogg")
		, m_pauseBuffer("resources/pause.wav")
		, m_unpauseBuffer("resources/unpause.wav")
		, m_pauseSound(m_pauseBuffer)
		, m_unpauseSound(m_unpauseBuffer)
	{
		m_inGameMusic.setLooping(true);
	}

	sf::SoundBuffer m_jumpBuffer;
	sf::SoundBuffer m_damageBuffer;

	sf::SoundBuffer m_pauseBuffer;
	sf::SoundBuffer m_unpauseBuffer;

	sf::Sound m_jumpSound;
	sf::Sound m_collisionSound;

	sf::Sound m_pauseSound;
	sf::Sound m_unpauseSound;

	sf::Music m_inGameMusic;
	sf::Music m_titleMusic;
};