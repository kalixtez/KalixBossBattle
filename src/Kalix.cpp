#include "Kalix.hpp"
#include <iostream>

int LUAi_GetEntityStatus(lua_State* luaPtr)
{
  Kalix* entity = (Kalix*) lua_topointer(luaPtr, -1);
  lua_settop(luaPtr, 0);
  float dirX = entity->et_getDirection();
  std::cout << "Direction:" << dirX << std::endl;
  bool jumping = entity->et_getJumping();
  std::cout << "is jumping?" << jumping << std::endl;
  lua_pushnumber(luaPtr, dirX);
  lua_pushboolean(luaPtr, jumping);

  return 2;
}

Kalix::Kalix()
m_script("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\src\\script\\scripts\\kalix.lua")
{
  m_script.registerFunction("GetStatus", LUAi_GetEntityStatus);
  et_Init();
}

void Kalix::et_Main(sf::RenderWindow& window, float elapsedTime)
{
  et_HandleInput();

  lua_getglobal(m_script.m_luaState, "Main");
  lua_pushlightuserdata(m_script.m_luaState, (void*) this);
  lua_pushnumber(m_script.m_luaState, elapsedTime);
  lua_pcall(m_script.m_luaState, 2, 2, 0);

  m_CoordX = (float) lua_tonumber(m_script.m_luaState, -2);
  m_CoordY = (float) lua_tonumber(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);

  std::cout << "Coord X:" << m_CoordX << std::endl;
  std::cout << "Coord Y:" << m_CoordY << std::endl;

  m_Sprite.setPosition(m_CoordX, m_CoordY);

  et_DrawEntity(window);
}

void Kalix::et_LoadSprites()
{
  sf::Texture texture;
  texture.loadFromFile("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\assets\\kalix_spt\\kalix_idle_hair.png");
  m_spriteSheet.push_back(texture);
  m_Sprite.setTexture(m_spriteSheet[0]);
}

void Kalix::et_Init()
{
  m_Speed_x = 2;
  m_Speed_y = 2;
  m_Initial_x = 200;
  m_Initial_y = 200;
  m_DirX = 0;
  m_Jumping = false;
  m_CoordX = m_Initial_x;
  m_CoordY = m_Initial_y;

  m_Health = 100;
  et_LoadSprites();
}

float Kalix::et_getDirection()
{
  return m_DirX;
}

bool Kalix::et_getJumping()
{
  return m_Jumping;
}

void Kalix::et_DrawEntity(sf::RenderWindow& window)
{
  window.draw(m_Sprite);
}

void Kalix::et_HandleInput()
{
  m_DirX = 0;
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    if(m_Jumping)
      {}
    else
      {m_Jumping = true;}
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    m_DirX = -1;
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    m_DirX = 1;
  }
}
