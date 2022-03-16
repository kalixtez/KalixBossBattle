#ifndef GAME_APP
#define GAME_APP

#include "Scene.hpp"
#include "EventManager.hpp"
#include <Graphics.hpp>
#include <Clock.hpp>

class Game
{
  public:
    Game(unsigned int, unsigned int);

    int gameLoop();

  private:
    void windowEventHandler();

    const unsigned int WND_WIDTH, WND_HEIGHT; //Window dimensions
    unsigned int DEF_POSX, DEF_POSY; //Window initial position on the screen.
    const char* m_AppName = "KLS";

    sf::RenderWindow m_GameWindow;
    Kalix kalix;
    sf::Clock clock;
    sf::Time elapsedTime;
    Scene* m_scene;

    EventManager m_EventManager;
};

#endif
