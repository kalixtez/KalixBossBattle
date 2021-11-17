#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include "Script.hpp"

class Entity
{
  protected:
    sf::Texture m_currentTexture;
    unsigned int m_XCOORD, m_YCOORD;
    std::vector<sf::Sprite> m_spriteSheet;

    unsigned int initial_x, initial_y;
    int speed_x, speed_y;
    int health;

    virtual void et_Update(lua_State*);
    virtual void et_LoadSprites(const char*);

    LuaScript m_script;

  public:
    virtual void et_DrawEntity(sf::RenderWindow&);
    virtual void et_Init();
    //virtual void lua_setObject(); Might work, but won't use it.
    virtual void et_getInitials();

    Entity();
    ~Entity();
}

int LUAi_GetInitials(lua_State* luaPtr)
{
  Entity* ptrEntity = (Entity*) lua_topointer(luaPtr, -1);
  double initial_x, initial_y, health = ptrEntity->et_getInitials();
  lua_pushnumber(luaPtr, initial_x);
  lua_pushnumber(luaPtr, initial_y);
  lua_pushnumber(luaPtr, initial_x);

  return 3;
}

int LUAi_DrawEntity(lua_State* luaPtr)
{
  Entity* ptrEntity = (Entity*) lua_topointer(luaPtr, -1);
  ptrEntity->et_DrawEntity();
  return 0;
}


#endif
