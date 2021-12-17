#include "GameApp.hpp"
#include <iostream>

Game::Game(unsigned int WDD_width, unsigned int WND_height)
: WND_WIDTH(WDD_width), WND_HEIGHT(WND_height), m_GameWindow(sf::VideoMode(WND_WIDTH, WND_HEIGHT), m_AppName)
{
  m_GameWindow.setFramerateLimit(60);
  if(!m_EventManager.LoadBindings("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\config\\keyconfig.cfg"))
    std::cout << "Could not open key configuration file" << std::endl;

  m_EventManager.m_bindings.find("MoveRight")->second->AddCallback(&Kalix::et_HandleInput, &kalix);
  m_EventManager.m_bindings.find("MoveLeft")->second->AddCallback(&Kalix::et_HandleInput, &kalix);
  m_EventManager.m_bindings.find("Jump")->second->AddCallback(&Kalix::et_HandleInput, &kalix);
}

int Game::gameLoop()
{
  while(m_GameWindow.isOpen())
  {
    windowEventHandler();
    m_EventManager.HandleInput();
    float elapsed = elapsedTime.asSeconds();
    m_GameWindow.clear(sf::Color::Black);
    kalix.et_Main(m_GameWindow, elapsed);
    m_GameWindow.display();
    elapsedTime = clock.restart();
  }

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
