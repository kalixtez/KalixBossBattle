#include "EventManager.hpp"

bool EventManager::LoadBindings(std::string path)
{
  std::string separator = "-";
  std::ifstream bindings_file;
  bindings_file.open(path);

  if (!bindings_file.is_open()){
    std::cout << "! Failed loading the keyconfig." << std::endl;
    return false;
  }

  std::string line;
  while(std::getline(bindings_file, line))
  {
    std::string binding_name;
    std::string has_default;
    std::stringstream s_stream(line);

    s_stream >> has_default;

    s_stream >> binding_name;
    Binding* newbind = new Binding(binding_name);

    if(has_default == "D")
      newbind->m_hasDefault = true;

    while(!s_stream.eof())
    {
      std::string type_and_key;
      s_stream >> type_and_key;

      if(s_stream.eof())
      {
        newbind->m_eventDetail = std::stoi(type_and_key);
        break;
      } //If we have reached the end of the string, that means we have reached the event detail.


      int separator_pos = type_and_key.find("-");
      if(separator_pos == std::string::npos)
      {
        std::cout << "No delimiter found in binding, check the cfg file" << binding_name << std::endl;
        break;
      }

      EventType type = EventType(std::stoi(type_and_key.substr(0, separator_pos)));
      int code = std::stoi(type_and_key.substr(separator_pos + 1, -1));
      EventInfo info = EventInfo(code);

      newbind->AddEvent(type, info);
    }

      if(!AddBinding(newbind))
      {
        delete newbind;
        newbind = nullptr;
      }
  }

bindings_file.close();
return true;
}


void EventManager::HandleInput()
{
  for(auto &binding : m_bindings) //m_bindings is an unordered_map that contains a std::string and a Binding pointer as its first and second members.
  {
    Binding* bind = binding.second;
    for(auto &event : bind->m_events) //m_events is a vector of std::pair<EventType, EventInfo> with event type being the code of
    {                                   //the event and EventInfo being the event specific details of such event e.g keycode, mouse button code, etc.
      switch(event.first)
      {
        case(EventType::KeyDown):
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(event.second.sm_keyCode))) //Check if the key bound to an event is pressed.
          {
            ++(bind->m_eventCount); //Increment the event counter, keep reading a few more lines to know why.
          }
          break;
      /*
        There can be more event types in here, but for now all events will be keypresses.
        ...
        ...
        ...
      */
      }
    }

    if(bind->m_eventCount == bind->m_events.size()) //This is why: if the event counter is equal to the number of events in the binding, we callback the function bound to the binding.
      { //(The event count being the same as the size of the m_events means that all events that need to happen have happened)
        bind->m_callback(bind->m_eventDetail); //Call the function wrapper with the event detail as the parameter.
      }

    bind->m_eventCount = 0;
  }
}
