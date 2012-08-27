#include "ScriptInterface.h"
#include "Script.h"
#include "Object.h"
#include "World.h"
#include "IDestroyable.h"

ScriptInterface :: ScriptInterface(Script* script, World* world, ObjectFactory* factory)
{
    assert(script);

    m_pScript = script;
    m_pState = script->state();
    m_pThread = script->thread();
    m_pWorld = world;
    m_pFactory = factory;

    lua_pushnumber(m_pState, System::get().w());
    lua_setglobal(m_pState, "SCREEN_W");
    lua_pushnumber(m_pState, System::get().h());
    lua_setglobal(m_pState, "SCREEN_H");

    m_pScript->setCallback("spawn", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1, ""));
    m_pScript->setCallback("backdrop", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1, "backdrop"));
    m_pScript->setCallback("enemy", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1, "enemy"));
    m_pScript->setCallback("particle", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1, "particle"));
    m_pScript->setCallback("item", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1, "item"));

    m_pScript->setCallback("spawn_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1, ""));
    m_pScript->setCallback("backdrop_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1, "backdrop"));
    m_pScript->setCallback("enemy_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1, "enemy"));
    m_pScript->setCallback("particle_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1, "particle"));
    m_pScript->setCallback("item_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1, "item"));

    m_pScript->setCallback("unhook", std::bind(&ScriptInterface::cbUnhook, this, std::placeholders::_1));
    m_pScript->setCallback("pos", std::bind(&ScriptInterface::cbPosition, this, std::placeholders::_1));
    m_pScript->setCallback("vel", std::bind(&ScriptInterface::cbVelocity, this, std::placeholders::_1));
    m_pScript->setCallback("size", std::bind(&ScriptInterface::cbSize, this, std::placeholders::_1));
    m_pScript->setCallback("depth", std::bind(&ScriptInterface::cbDepth, this, std::placeholders::_1));
    m_pScript->setCallback("health", std::bind(&ScriptInterface::cbHealth, this, std::placeholders::_1));
    m_pScript->setCallback("max_health", std::bind(&ScriptInterface::cbMaxHealth, this, std::placeholders::_1));
    
    // more:
    // damage() -- for getting/setting damage
    // clone_hook() -- spawn a copy of an item
    // kill(), hurt(), heal() -- things that trigger callbacks

    m_pScript->setCallback("clear", std::bind(&ScriptInterface::cbClear, this, std::placeholders::_1));
    m_pScript->setCallback("exists", std::bind(&ScriptInterface::cbExists, this, std::placeholders::_1));

    m_pScript->setCallback("music", std::bind(&ScriptInterface::cbMusic, this, std::placeholders::_1));
}

ScriptInterface :: ~ScriptInterface()
{
    
}

int ScriptInterface :: cbSpawnHook(lua_State* state, std::string type)
{
    std::string name = luaL_checkstring(state, 1);
    std::shared_ptr<Object> object;
    //if(!(object = m_pFactory->create("data/objects/" + name + ".ini")))
    //    object = m_pFactory->create("data/backdrops/" + name + ".ini");
    object = m_pFactory->create(name, type);
    int i = -1;
    assert(object);
    if(object)
    {
        //std::shared_ptr<IScriptable> scriptable = std::dynamic_pointer_cast<IScriptable>(object);
        // following code is O(hell no) -- TODO: fix
        for(i=0;;i++)
            if(m_Hooks.find(i) == m_Hooks.end())
            {
                m_Hooks[i] = {
                    std::weak_ptr<IScriptable>(std::dynamic_pointer_cast<IScriptable>(object))
                };
                //m_Hooks[i].push_back(std::weak_ptr<IScriptable>(std::dynamic_pointer_cast<IScriptable>(object)));
                break;
            }
    }

    if(i >= 0)
    {
        lua_pushnumber(state, i*1.0);
        return 1;
    }
    // TODO: something went wrong...
    return 0;
}

int ScriptInterface :: cbSpawn(lua_State* state, std::string type)
{
    std::string name = luaL_checkstring(state, 1);
    // TODO: keep scripts from accessing filesystem outside of data folder
    
    m_pFactory->create(name, type);
    return 0;
}

int ScriptInterface :: cbUnhook(lua_State* state)
{
    unsigned int id = (unsigned int)round_int(lua_tonumber(state, 1));
    m_Hooks.erase(id);
    return 0;
}

int ScriptInterface :: cbPosition(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        Object* o = dynamic_cast<Object*>(objects[0].get());
        lua_pushnumber(state, o->pos().x);
        lua_pushnumber(state, o->pos().y);
        return 2;
    }
    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    
    foreach(auto& obj, objects)
    {
        assert(obj.get());
        Object* o = dynamic_cast<Object*>(obj.get());
        o->pos(Vector2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3)));
    }

    return 0;
}

int ScriptInterface :: cbCenter(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        Object* o = dynamic_cast<Object*>(objects[0].get());
        lua_pushnumber(state, o->center().x);
        lua_pushnumber(state, o->center().y);
        return 2;
    }
    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    
    foreach(auto& obj, objects)
    {
        assert(obj.get());
        Object* o = dynamic_cast<Object*>(obj.get());
        o->center(Vector2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3)));
    }

    return 0;
}



int ScriptInterface :: cbVelocity(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        Object* o = dynamic_cast<Object*>(objects[0].get());
        lua_pushnumber(state, o->vel().x);
        lua_pushnumber(state, o->vel().y);
        return 2;
    }

    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    
    foreach(auto& obj, objects)
    {
        assert(obj.get());
        Object* o = dynamic_cast<Object*>(obj.get());
        o->vel(Vector2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3)));
    }
    return 0;
}

int ScriptInterface :: cbHealth(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        IDestroyable* o = dynamic_cast<IDestroyable*>(objects[0].get());
        lua_pushnumber(state, o->health());
        return 1;
    }

    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    
    foreach(auto& obj, objects)
    {
        assert(obj.get());
        IDestroyable* o = dynamic_cast<IDestroyable*>(obj.get());
        o->health(round_int(lua_tonumber(state, 2)));
    }
    return 0;
}

int ScriptInterface :: cbMaxHealth(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        IDestroyable* o = dynamic_cast<IDestroyable*>(objects[0].get());
        lua_pushnumber(state, o->maxHealth());
        return 1;
    }

    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    
    foreach(auto& obj, objects)
    {
        assert(obj.get());
        IDestroyable* o = dynamic_cast<IDestroyable*>(obj.get());
        o->maxHealth(round_int(lua_tonumber(state, 2)));
    }
    return 0;
}


int ScriptInterface :: cbSize(lua_State* state)
{
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));
    if(lua_gettop(state) == 1)
    {
        if(objects.size() != 1)
            return 0; //error

        Object* o = dynamic_cast<Object*>(objects[0].get());
        lua_pushnumber(state, o->size().x);
        lua_pushnumber(state, o->size().y);
        return 2;
    }

    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    return 0;
}


int ScriptInterface :: cbClear(lua_State* state)
{
    lua_pushboolean(state, m_pWorld->hasEnemies() ? 0 : 1);
    return 1;
}

int ScriptInterface :: cbDepth(lua_State* state)
{
    if(lua_gettop(state) == 0)
        return 0;

    //std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);
    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));

    if(lua_gettop(state) == 0) // get depth()
    {
        if(objects.size() != 1)
            return 0; // error
        Object* o = dynamic_cast<Object*>(objects[0].get());
        lua_pushnumber(state, o->sprite().depth());
        return 1;
    }
        
    foreach(auto& obj, objects) // set depth()
    {
        assert(obj.get());
        Object* o = dynamic_cast<Object*>(obj.get());
        o->sprite().depth((float)lua_tonumber(state, 2));
    }
    return 0;
}

//int ScriptInterface :: cbImage(lua_State* state)
//{
//    std::vector<std::shared_ptr<IScriptable>> objects = hook(round_int(lua_tonumber(state, 1)));

//    if(lua_gettop(state) == 1)
//    {
//        lua_pushboolean(state, o->setImage(std::string(lua_checkstring(state,2))));
//        return 1;
//    }
//    //o->image() TODO: get image name
//    return 0;
//}

int ScriptInterface :: cbExists(lua_State* state)
{
    unsigned int id = round_int(lua_tonumber(state, 1));
    lua_pushnumber(state, flush(id));
    return 1;
}

int ScriptInterface :: cbPlayers(lua_State* state)
{
    return 0;
}

int ScriptInterface :: cbEnemies(lua_State* state)
{
    //lua_pushboolean(state, m_pWorld->hasEnemies() ? 0 : 1);
    return 0;
}

int ScriptInterface :: cbMusic(lua_State* state)
{
    std::string name = luaL_checkstring(state, 1);
    if(!m_pWorld->music())
        m_pWorld->music(name);
    if(m_pWorld->music())
        m_pWorld->music()->play(Audio::Stream::REPEAT | Audio::Stream::CONTINUE);
    return 0;
}


//int ScriptInterface :: cbStats(lua_State* state)
//{
    
//}
