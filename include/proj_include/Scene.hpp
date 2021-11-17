#ifndef SCENE_H
#define SCENE_H

#include "Entity.hpp"
#include "Kalix.hpp"

class Scene
{
  public:
    Scene();
    ~Scene();

    int sc_setLevel(); //Set the current level.

    int sc_Draw();
    int sc_Update();
    int sc_Display();

  private:
    //Camera* m_camera;
    //Level* m_Level;
    //std::vector<Entity> m_entities;

    Scene(const Scene&) = delete;
}

#endif
