#ifndef KALIX_H
#define KALIX_H

#include "Entity.hpp"


class Kalix : public Entity
{
public:
  Kalix();

  void et_HandleInput();
  void et_LoadSprites();
  const char* m_sname = "kalix.lua";
  void et_DrawEntity(sf::RenderWindow&);
  void et_Init();
  void et_Main(sf::RenderWindow&, float);
  //virtual void lua_setObject(); Might work, but won't use it.
  int et_getDirection();
  bool et_getJumping();

private:
  LuaScript m_script;

};

#endif
