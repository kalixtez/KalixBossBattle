#include "include\proj_include\GameApp.hpp"

Game::Game(unsigned int WDD_width, unsigned int WND_height)
: WND_WIDTH(WDD_width), WND_HEIGHT(WND_height)
{
  m_GameWindow = new RenderWindow(sf::VideoMode(WND_WIDTH, WND_HEIGHT)), m_AppName);
  loadEntityAssets();
  loadLevels();
}

int Game::gameLoop()
{
  while(m_GameWindow.isOpen())
  {
    windowEventHandler();
  }
  return 0;
}


int Game::windowEventHandler()
{
  sf::Event win_event;
  while(m_GameWindow.pollEvent(win_event))
  {
    if (event.type == sf::Event::Closed)
      {
        m_GameWindow.close();
      }
  return 0;
}

int Game::inputHandler()
{
  


  return 0;
}
