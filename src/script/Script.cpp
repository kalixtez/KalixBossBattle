#include "Script.hpp"

LuaScript::LuaScript(const char* script_path)
{
  m_luaState = luaL_newstate();
	if(luaL_loadfile(m_luaState, script_path))
    std::cout << "Loading of the kalix script failed" << std::endl;
  else
  {
    std::cout << "Lua loaded successfuly" << std::endl;
    lua_pcall(m_luaState, 0, LUA_MULTRET, 0);
  }
}

void LuaScript::callFunction(const char* fname)
{
    lua_getglobal(m_luaState, fname);
}

void LuaScript::registerFunction(const char* funcName, lua_CFunction fptr)
{
  lua_pushcfunction(m_luaState, fptr);
  lua_setglobal(m_luaState, funcName);
}
