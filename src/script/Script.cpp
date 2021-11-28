#include "Script.hpp"

LuaScript::LuaScript(const char* script_path)
{
  m_luaState = luaL_newstate();
}

void LuaScript::callFunction(const char* fname)
{
    lua_getglobal(m_luaState, fname);
    lua_pcall(m_luaState, 0, 0 , 0);
}

void LuaScript::registerFunction(const char* funcName, lua_CFunction fptr)
{
  lua_pushcfunction(m_luaState, fptr);
  lua_setglobal(m_luaState, funcName);
}
