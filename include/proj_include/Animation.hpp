#ifndef ANIMATION_H
#define ANIMATION_H

#include <Graphics.hpp>
#include <unordered_map>
#include <include\rapidjson\document.h>
#include <utility>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <lua.hpp>


//Globals.
int LUAi_AddAnimations(lua_State*);
int LUAi_GetCurrentAnimation(lua_State*);

//Functions of the library.
int LUAi_GetFrametime(lua_State*);
int LUAi_NextFrame(lua_State*);
int LUAi_ResetPastAnim(lua_State*);
int LUAi_PlayCurrentAnim(lua_State*);

struct UniqueAnimation
{
  UniqueAnimation()
  {

  }

  unsigned int m_frameNumber; //Number of frames of an animation.
  unsigned int m_currentFrame = 0;
  std::vector<float> m_FrameTimes; //Vector that stores the duration of each frame.
  float m_AnimationTime = 0; //Total time since animation started playing.
  sf::Texture m_Texture;
  unsigned int m_AnimID;
  bool m_FirstTime = true;

  void PlayAnim(sf::RenderWindow& window, sf::Sprite& sprite)
  {
    window.draw(sprite);
    if(m_FirstTime)
    {
      sprite.setTexture(m_Texture);
      sprite.setTextureRect(sf::Rect<int>(32, 0, 32, 48));
      m_currentFrame = 0;
      m_AnimationTime = 0;
      m_FirstTime = false;
    }

    else
      sprite.setTextureRect(sf::Rect<int>(32*m_currentFrame, 0, 32, 48));

    if(m_currentFrame >= m_frameNumber)
        {
          m_AnimationTime = 0;
          m_currentFrame = 0;
        }
  }

};

using Anims = std::unordered_map<std::string, UniqueAnimation*>;

class Animation
{
  public:
    Animation()
    {

    }
    UniqueAnimation* m_pastAnimation;
    const char* m_CurrentAnimationName; // of an entity.
    UniqueAnimation* m_CurrentAnimation;  // of an entity.
    Anims m_Animations; //Every animation will be identified with a number, which will be loaded from a file describing the  set of animations

  public:
      void PlayCurrentAnimation();
      void EntityLoadAnimations(lua_State*, const std::string&);
};


#endif
