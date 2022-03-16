#include "Entity.hpp"

int LUAi_GetEntityStatus(lua_State* luaPtr)
{
  Entity* entity = (Entity*) lua_topointer(luaPtr, -1);

  float dirX = entity->et_getDirection();
  bool jumping = entity->et_getJumping();
  lua_pushnumber(luaPtr, dirX);
  lua_pushboolean(luaPtr, jumping);

  return 2;
}
