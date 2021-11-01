#ifndef GAME_APP
#define GAME_APP

#include "include\proj_include\Scene.hpp"
#include "include\SFML\Graphics.hpp"

class Game
{
  public:
    Game();
    ~Game();

    int gameLoop();


  private:
    int loadAssets();
    int loadLevels();
    void Update();

    unsigned int WND_WIDTH, WND_HEIGHT; //Window dimensions
    unsigned int DEF_POSX, DEF_POSY; //Window initial position on the screen.
    const char* AppName = "KLS";

    sf::RenderWindow m_GameWindow;

    Scene m_scene;

}

#endif
