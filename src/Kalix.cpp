#include "Kalix.hpp"
#include <iostream>
#include <vector>


Kalix::Kalix():
m_script("C:\\Users\\OmGIt\\OneDrive\\Escritorio\\C++ practice\\KalixBossBattle\\src\\script\\scripts\\kalix.lua" , (void*) this)
{
  m_script.registerFunction("GetStatus", LUAi_GetEntityStatus);
  et_Init();
}

void Kalix::et_Main(sf::RenderWindow& window, float elapsedTime)
{

  lua_getglobal(m_script.m_luaState, "Main");
  lua_pushlightuserdata(m_script.m_luaState, (void*) this);
  lua_pushnumber(m_script.m_luaState, elapsedTime);
  lua_pcall(m_script.m_luaState, 2, 5, 0);

  m_CoordX = (float) lua_tonumber(m_script.m_luaState, -5);
  m_CoordY = (float) lua_tonumber(m_script.m_luaState, -4);
  m_Jumping = (bool) lua_toboolean(m_script.m_luaState, -3);
  const char* animID = lua_tostring(m_script.m_luaState, -2);
  float elapsedlua = (float) lua_tonumber(m_script.m_luaState, -1);

  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);
  lua_pop(m_script.m_luaState, -1);

  m_Sprite.setPosition(m_CoordX, m_CoordY);

  //std::cout << animID << '\n';
  //std::cout << elapsedlua << '\n';

  /*if(m_Jumping == false && m_DirX == 0)
    {
      if(m_entityAnim.m_CurrentAnimation != m_entityAnim.m_Animations.find("IdleOne")->second)
      {
        m_entityAnim.m_CurrentAnimation->m_FirstTime = true;
        m_entityAnim.m_CurrentAnimationName = m_entityAnim.m_Animations.find("IdleOne")->first.c_str();
        m_entityAnim.m_CurrentAnimation = m_entityAnim.m_Animations.find("IdleOne")->second;
      }
    }
    */

  m_DirX = 0;
  et_DrawEntity(window);

}

void Kalix::et_Init()
{
  m_DirX = 0;
  m_Jumping = false;
  m_CoordX = 200;
  m_CoordY = 200;

  m_Health = 100;
  m_entityAnim.m_CurrentAnimationName = m_entityAnim.m_Animations.find("IdleOne")->first.c_str();
  m_entityAnim.m_CurrentAnimation = m_entityAnim.m_Animations.find("IdleOne")->second;
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
  m_entityAnim.m_CurrentAnimation->PlayAnim(window, m_Sprite);
}

void Kalix::et_HandleInput(int keyCode) //Receive keycode from the event handler.
{
  if(keyCode == 74)
  {
    if(m_Jumping)
      {}
    else
      {
        m_Jumping = true;
      }
      /*
      m_entityAnim.m_CurrentAnimation->m_FirstTime = true;
      m_entityAnim.m_CurrentAnimationName = m_entityAnim.m_Animations.find("Jumping")->first.c_str();
      m_entityAnim.m_CurrentAnimation = m_entityAnim.m_Animations.find("Jumping")->second;
      */
  }
  if(keyCode == -1)
  {
    m_DirX = -1;
  /*
    if(m_entityAnim.m_CurrentAnimation != m_entityAnim.m_Animations.find("Running")->second)
    {
      m_entityAnim.m_CurrentAnimation->m_FirstTime = true;
      m_entityAnim.m_CurrentAnimationName = m_entityAnim.m_Animations.find("Running")->first.c_str();
      m_entityAnim.m_CurrentAnimation = m_entityAnim.m_Animations.find("Running")->second;
    }
    */
  }
  else if(keyCode == 1)
  {
    m_DirX = 1;
/*
    if(m_entityAnim.m_CurrentAnimation != m_entityAnim.m_Animations.find("Running")->second)
    {
      m_entityAnim.m_CurrentAnimation->m_FirstTime = true;
      m_entityAnim.m_CurrentAnimationName = m_entityAnim.m_Animations.find("Running")->first.c_str();
      m_entityAnim.m_CurrentAnimation = m_entityAnim.m_Animations.find("Running")->second;
    }
    */
  }

}
