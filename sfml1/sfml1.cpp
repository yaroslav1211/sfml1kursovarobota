#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Player.h"
#include "Background.h"
#include "Platform.h"
#include "PlatformHolder.h"
#include "PhysicsEngine.h"
#include "SoundManager.h"
#include "GameHUD.h"
#include "GameWorld.h"
#include "GameStateManager.h"
#include "GameState.h"

void handleWindowEvents(sf::Window& window)
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }
        if (auto keyPressedEvent = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressedEvent->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode{ {1920, 1080} }, "Doodle Jump, pt.6");
    //window.setFramerateLimit(560);

    sf::Clock mainClock;

    GameWorld gameWorld(&window);
    GameStateManager gameStateManager(&gameWorld, GameStateId::TitleScreen, &window);

    SoundManager::getInstance().playInGameMusic();
    GameHUD gameHud(&window);

    while (window.isOpen())
    {
        const float dt = mainClock.restart().asSeconds();

        handleWindowEvents(window);

        //UPDATE STEP
        gameStateManager.getCurrentGameState()->update(dt);
        gameHud.update(dt);

        //DRAW STEP
        gameStateManager.getCurrentGameState()->draw();
        gameHud.draw();

        gameStateManager.getCurrentGameState()->updateState();

        //DISPLAY STEP
        window.display();
    }

    return 0;
}