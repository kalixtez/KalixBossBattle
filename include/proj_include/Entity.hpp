#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

class Entity
{
  private:
      sf::Sprite m_currentTexture;
      unsigned int m_XCOORD, m_YCOORD;
      sf::Sprite m_spriteSheet;

  protected:
    virtual void et_Init(const char* texturePath);
    virtual void et_Update();

  public:
    virtual void et_DrawEntity(sf::RenderWindow& window);
    Entity();
    ~Entity();
}

#endif
