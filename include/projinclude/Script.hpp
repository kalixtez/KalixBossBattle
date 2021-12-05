#ifndef SCRIPT_H
#define SCRIPT_H

#include <lua.hpp>
#include <iostream>

class LuaScript
{

public:
  LuaScript(const char*);

  void callFunction(const char*); //Use lightuserdata to pass class pointers to Lua. This is important to know which object is calling back.
  void registerFunction(const char*, lua_CFunction);
  lua_State* m_luaState;

private:
  const char* m_Path;
  bool m_InitWasCalled;

};


#endif
