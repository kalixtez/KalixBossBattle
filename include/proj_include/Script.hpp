#ifndef SCRIPT_H
#define SCRIPT_H

#include "include\lua\lua.hpp"

class LuaScript
{

public:
  Script();
  ~Script();

  void callFunction(const char*, void*); //Use userdata to pass class pointers to Lua. This is important to know which object is calling back.
  void registerFunction(const char*);

private:
  const char* m_Path;
  lua_State* m_luaState
  bool m_InitWasCalled;

  Script(const Script&) = delete;
}


#endif
