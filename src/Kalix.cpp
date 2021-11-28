#include "Kalix.hpp"

int LUAi_GetEntityStatus(lua_State* luaPtr)
{
  Entity* entity = (Entity*) lua_topointer(luaPtr, -1);
  int dirX = entity->et_getDirection();
  bool jumping = entity->et_getJumping();
  lua_pushnumber(luaPtr, dirX);
  lua_pushboolean(luaPtr, jumping);

  return 2;
}

Kalix::Kalix():
m_script("kalix.lua")
{
  m_script.registerFunction("GetStatus", LUAi_GetEntityStatus);
  et_Init();
}

void Kalix::et_Main(sf::RenderWindow& window, float elapsedTime)
{
  Kalix* ptr = this;
  et_HandleInput();
  lua_getglobal(m_script.m_luaState, "Main");
  lua_pushlightuserdata(m_script.m_luaState, (void*) ptr);
  lua_pushnumber(m_script.m_luaState, elapsedTime);
  lua_pcall(m_script.m_luaState, 1, 0, 0);
  m_Sprite.setPosition(m_CoordX, m_CoordY);

  et_DrawEntity(window);
}

void Kalix::et_LoadSprites()
{
  sf::Texture texture;
  texture.loadFromFile("assets/kalix_spt/kalix_idle_hair.png");
  m_spriteSheet.push_back(texture);
  m_Sprite.setTexture(m_spriteSheet[0]);
}

void Kalix::et_Init()
{
  m_Speed_x = 2;
  m_Speed_y = 2;
  m_Initial_x = 100;
  m_Initial_y = 200;
  m_Health = 100;
  et_LoadSprites();
}

int Kalix::et_getDirection()
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
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
  {
    m_Jumping = true;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
  {
    m_DirX = -1;
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
  {
    m_DirX = 1;
  }
  else {m_DirX = 0;}
}
