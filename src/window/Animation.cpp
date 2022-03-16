#include "Animation.hpp"
#include "Entity.hpp"


static const struct luaL_Reg animlib_reg[] =
{
 //{ "play", LUAi_PlayCurrentAnim },
 { "frametime", LUAi_GetFrametime },
 { "next_frame", LUAi_NextFrame },
 {NULL, NULL}
};

void Animation::EntityLoadAnimations(lua_State* luaptr, const std::string& path)
{
  std::ifstream jsonFile(path);
  std::stringstream jsonStream;
  jsonStream << jsonFile.rdbuf();

  std::string json = jsonStream.str();
  rapidjson::Document jsondoc;
  jsondoc.Parse(json.c_str());

  rapidjson::Value& anims_ref = jsondoc["Animations"];

  if(anims_ref.IsArray())
  {

    lua_newtable(luaptr);

    for(auto& animr : anims_ref.GetArray())
    {

        UniqueAnimation* sprite = (UniqueAnimation*)lua_newuserdata(luaptr, sizeof(UniqueAnimation));
        sprite->m_frameNumber = animr["Number_of_frames"].GetInt();
        sprite->m_FrameTimes.resize(animr["Frametime"].IsArray() ? animr["Frametime"].GetArray().Size() : 1);
        sprite->m_AnimID = animr["Animation_ID"].GetInt();
        unsigned char count = 0;

        if(animr["Frametime"].IsArray())
        {
          for(auto& frametimes : animr["Frametime"].GetArray())
          {
            sprite->m_FrameTimes.at(count) = (float) frametimes.GetDouble();
            if(count > sprite->m_FrameTimes.max_size())
              break;
            count++;
          }
        }
        else
          sprite->m_FrameTimes.push_back((float) animr["Frametime"].GetDouble());

        sprite->m_Texture.loadFromFile(animr["Path"].GetString());

        luaL_setmetatable(luaptr, "AnimationMetatable"); //The metatable "AnimationMetatable" MUST already exist the moment this line here is executed. The function that creates the metatable is called the moment a LuaScript object is created.
        // And a script can only call the EntityLoadAnimations function if it exists, therefore, the table does exists at this point... Unless there were loading errors...

        lua_setfield(luaptr, -2, animr["Name"].GetString()); //Maybe use lua_seti() to index the animationList table with the IDs and not the names?
        //std::cout << animr["Path"].GetString() << '\n';

        // lua_setfield removes the sprite object from the stack, so when this function returns, the object at the top of the stack is the table where all objects are stored.
        m_Animations.emplace(animr["Name"].GetString(), sprite);

    }
    //std::cout << lua_istable(luaptr, -1);
  }

  else
    std::cout << "An error ocurred while parsing the JSON file." << "\n";

}

//This function will be registered as a global in Lua.
int LUAi_AddAnimations(lua_State* luaPtr)    //This function will be called from Lua, to load all of the animations into a state that's associated with an entity.
{
  Entity* entity = (Entity*) lua_topointer(luaPtr, -2);
  const char* path = lua_tostring(luaPtr, -1);

  entity->m_entityAnim.EntityLoadAnimations(luaPtr, path); //When this function returns, a table that contains all of the entity's animation (represented as userdatas) must be at the top of the stack, so it is this value the return value of this fucntion.
  return 1;

}

//This function will be registered as a global in Lua.
int LUAi_GetCurrentAnimation(lua_State* luaPtr)
{
  Entity* entity = (Entity*) lua_topointer(luaPtr, -1);
  lua_pushstring(luaPtr, entity->m_entityAnim.m_CurrentAnimationName);

  return 1;
}

int LUAi_NextFrame(lua_State* luaPtr)
{
  UniqueAnimation* anim = (UniqueAnimation*) lua_touserdata(luaPtr, -1);
  anim->m_currentFrame++;

  return 0;
}

int LUAi_GetFrametime(lua_State* luaPtr)
{
  UniqueAnimation* anim = (UniqueAnimation*) lua_touserdata(luaPtr, -1);
  lua_pushnumber(luaPtr, anim->m_FrameTimes[anim->m_currentFrame]);

  return 1;
}

int luaopen_animtable(lua_State* luaPtr) //This function MUST never be called in the program by itself, only by luaL_requiref(), as the lib opener fucntion.
{
  luaL_newmetatable(luaPtr, "AnimationMetatable"); //Push the metatable for the animation userdata.
  luaL_newlib(luaPtr, animlib_reg); //Create the table that contains the functions.

  lua_pushvalue(luaPtr, -1); //Duplicate it, right now the stack is, from top to bottom, animlib, animlib, AnimationMetatable.
  lua_setfield(luaPtr, -3, "__index"); // Set the "__index" field of the metatable equal to the table where the functions are registered.

  return 1;
}
