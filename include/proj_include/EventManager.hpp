#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <Graphics.hpp>
#include <functional>
#include <vector>
#include <utility>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

enum class EventType
{
   KeyDown = sf::Event::KeyPressed,
   KeyUp = sf::Event::KeyReleased,
   MButtonDown = sf::Event::MouseButtonPressed,
   MButtonUp = sf::Event::MouseButtonReleased,
   MouseWheel = sf::Event::MouseWheelMoved,
   WindowResized = sf::Event::Resized,
   GainedFocus = sf::Event::GainedFocus,
   LostFocus = sf::Event::LostFocus,
   MouseEntered = sf::Event::MouseEntered,
   MouseLeft = sf::Event::MouseLeft,
   Closed = sf::Event::Closed,
   TextEntered = sf::Event::TextEntered,
   Keyboard = sf::Event::Count + 1, Mouse, Joystick
};

struct EventInfo
{
  EventInfo(){}
  EventInfo(int keyCode)
  {sm_keyCode = keyCode;}

  unsigned int sm_keyCode;
};

using Events = std::vector<std::pair<EventType, EventInfo>>;
using Callback = std::function<void(int)>;

struct Binding
{
  Binding(std::string name):
    m_eventCount(0), m_eventDetail(0), m_name(name)
  {

  }

  template<class T>
  void AddCallback(void (T::*instance_method)(int), T* instance)
  {
    m_callback = std::bind(instance_method, instance, std::placeholders::_1);
  }
  void AddEvent(EventType eventType, EventInfo eventInfo)
  {
    m_events.emplace_back(eventType, eventInfo); // You can use the emplace_back method to add a pair without explicitly calling std::make_pair().
  }

  Events m_events;
  std::string m_name;
  unsigned int m_eventDetail;
  Callback m_callback;
  unsigned int m_eventCount;
  bool m_hasDefault = false;
};

using Bindings = std::unordered_map<std::string, Binding*>; //String to identify the binding with a name, e.g "PlayerMovement".

struct EventManager
{
  EventManager()
  {}
  bool AddBinding(Binding* binding)
  {
    if(m_bindings.find(binding->m_name) == m_bindings.end())
    {
      m_bindings.emplace(binding->m_name, binding);
      return true;
    }
    else
    {
      std::cout << "The binding" << binding->m_name << "already exists." << std::endl;
      return false;
    }
  }

  void HandleInput();

  bool LoadBindings(std::string);

  Bindings m_bindings;
};

#endif
