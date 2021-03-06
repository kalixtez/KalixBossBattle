#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <Graphics.hpp>
#include "Script.hpp"
#include "Animation.hpp"

int LUAi_GetEntityStatus(lua_State* luaPtr);

class Entity
{
public:
    sf::Sprite m_Sprite;
    float m_CoordX, m_CoordY;

    float m_Initial_x, m_Initial_y;
    int m_Speed_x, m_Speed_y;
    int m_Health;
    float m_DirX;
    bool m_Jumping;

    virtual void et_HandleInput(){};

    LuaScript m_script;
    Animation m_entityAnim;

    virtual void et_DrawEntity(sf::RenderWindow&){}
    virtual void et_Init(){}
    virtual void et_Main(sf::RenderWindow&, float){}
    //virtual void lua_setObject(); Might work, but won't use it.
    virtual float et_getDirection(){return m_DirX;}
    virtual bool et_getJumping(){return m_Jumping;}

    Entity(){

    }
};

#endif
