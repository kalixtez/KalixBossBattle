#include "Kalix.hpp"
#include <iostream>
#include <vector>

int LUAi_GetEntityStatus(lua_State* luaPtr)
{
  Entity* entity = (Entity*) lua_topointer(luaPtr, -1);
  lua_settop(luaPtr, 0);
  float dirX = entity->et_getDirection();
  std::cout << "Direction:" << dirX << std::endl;
  bool jumping = entity->et_getJumping();
  std::cout << "is jumping?" << jumping << std::endl;
  lua_pushnumber(luaPtr, dirX);
  lua_pushboolean(luaPtr, jumping);

  return 2;
}

Kalix::Kalix():
m_script("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\src\\script\\scripts\\kalix.lua")
{
  m_script.registerFunction("GetStatus", LUAi_GetEntityStatus);
  et_Init();
}

void Kalix::et_Main(sf::RenderWindow& window, float elapsedTime)
{

  lua_getglobal(m_script.m_luaState, "Main");
  lua_pushlightuserdata(m_script.m_luaState, (void*) this);
  lua_pushnumber(m_script.m_luaState, elapsedTime);
  lua_pcall(m_script.m_luaState, 2, 3, 0);

  m_CoordX = (float) lua_tonumber(m_script.m_luaState, -3);
  m_CoordY = (float) lua_tonumber(m_script.m_luaState, -2);
  m_Jumping = (bool) lua_toboolean(m_script.m_luaState, -1);

  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);

  m_Sprite.setPosition(m_CoordX, m_CoordY);

  et_DrawEntity(window);
  m_DirX = 0;
}

void Kalix::et_LoadSprites()
{
  sf::Texture texture;
  texture.loadFromFile("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\assets\\kalix_spt\\kalix_idle_hair.png");
  m_spriteSheet.push_back(texture);
  m_Sprite.setTexture(m_spriteSheet[0]);
  m_Sprite.setTextureRect(sf::Rect<int>(0, 0, 32, 32));
}

void Kalix::et_Init()
{
  m_DirX = 0;
  m_Jumping = false;
  m_CoordX = 200;
  m_CoordY = 200;

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

void Kalix::et_HandleInput(int keyCode) //Receive keycode from the event handler.
{
  m_DirX = 0;
  if(keyCode == 74)
  {
    if(m_Jumping)
      {}
    else
      {m_Jumping = true;}
  }
  if(keyCode == -1)
  {
    m_DirX = -1;
  }
  else if(keyCode == 1)
  {
    m_DirX = 1;
  }
}
