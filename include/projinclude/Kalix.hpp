#ifndef KALIX_H
#define KALIX_H

#include "Entity.hpp"


class Kalix : public Entity
{
public:
  Kalix();

  void et_HandleInput();
  void et_LoadSprites();
  void et_DrawEntity(sf::RenderWindow&);
  void et_Init();
  void et_Main(sf::RenderWindow&, float);

  float et_getDirection();
  bool et_getJumping();

  LuaScript m_script;
};

#endif
