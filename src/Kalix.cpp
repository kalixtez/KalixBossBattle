#include "include\proj_include\Kalix.hpp"

Kalix::Kalix():
speed_x(2), speed_y(2), health(100)
{
  m_script.registerFunction("GetInitials", LUAi_GetInitials);
  m_script.registerFunction("DrawEntity", LUAi_DrawEntity);
  et_Init();


}

/*void Kalix::lua_SetObject()
{
  Kalix* ptr = this;
  lua_pushlightuserdata(m_script.m_luaState, (void*) ptr); //This might work, but I'd rather to this the other way. (The one impelemented)
  lua_setglobal(m_script.m_luaState, "ptr");
}*/

void Kalix::et_Init()
{
  Kalix* ptr = this;

  lua_getglobal(m_script.m_luaState, "Init");
  lua_pushlightuserdata(m_script.m_luaState, (void*) ptr);
  lua_pcall(m_script.m_luaState, 1, 0, 0);
}

double Kalix::et_getInitials(lua_State* luaPtr)
{
  return speed_x, speed_y, health;
}

void Kalix::et_DrawEntity(sf::RenderWindow& window)
{

}
