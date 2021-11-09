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
    int inputHandler();
    int windowEventHandler();
    int loadEntityAssets();
    int loadLevels();
    void Update();

    const unsigned int WND_WIDTH, WND_HEIGHT; //Window dimensions
    unsigned int DEF_POSX, DEF_POSY; //Window initial position on the screen.
    const char* m_AppName = "KLS";

    sf::RenderWindow* m_GameWindow;
    sf::Keyboard* m_GameInput;

    Scene* m_scene;
}

#endif
