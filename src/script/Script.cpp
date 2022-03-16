#include "Script.hpp"

int luaopen_animtable(lua_State*);

LuaScript::LuaScript(const char* script_path, void* associated_entity)
{
  m_luaState = luaL_newstate();
  lua_pushlightuserdata(m_luaState, associated_entity);
  lua_setglobal(m_luaState, "ENTITY_PTR"); //Set a global pointer, pointing to the entity associated to the Lua state.

  registerFunction("LoadAnimations", LUAi_AddAnimations);
  registerFunction("GetCurrentAnimation", LUAi_GetCurrentAnimation);

  luaL_requiref(m_luaState, "animtable", luaopen_animtable, 1);

	if(luaL_loadfile(m_luaState, script_path))
    std::cout << "Loading of the kalix script failed" << std::endl;
  else
  {
    std::cout << "Lua loaded successfuly" << std::endl;
    lua_pcall(m_luaState, 0, LUA_MULTRET, 0);
  }
}


void LuaScript::registerFunction(const char* funcName, lua_CFunction fptr)
{
  lua_pushcfunction(m_luaState, fptr);
  lua_setglobal(m_luaState, funcName);
}
