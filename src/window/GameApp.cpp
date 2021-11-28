#include "GameApp.hpp"

Game::Game(unsigned int WDD_width, unsigned int WND_height)
: WND_WIDTH(WDD_width), WND_HEIGHT(WND_height), m_GameWindow(sf::VideoMode(WND_WIDTH, WND_HEIGHT), m_AppName)
{

}

int Game::gameLoop()
{
  while(m_GameWindow.isOpen())
  {
    windowEventHandler();
  }
  float elapsed = elapsedTime.asSeconds();
  kalix.et_Main(m_GameWindow, elapsed);
  elapsedTime = clock.getElapsedTime();
  return 0;
}


int Game::windowEventHandler()
{
  sf::Event win_event;
  while(m_GameWindow.pollEvent(win_event))
  {
    if (win_event.type == sf::Event::Closed)
      {
        m_GameWindow.close();
      }
  }
  return 0;
}
