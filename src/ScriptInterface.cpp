#include "ScriptInterface.h"
#include "Script.h"
#include "Object.h"

ScriptInterface :: ScriptInterface(Script* script, ObjectFactory* factory)
{
    assert(script);

    m_pScript = script;
    m_pState = script->state();
    m_pThread = script->thread();
    m_pFactory = factory;

    m_pScript->setCallback("spawn", std::bind(&ScriptInterface::cbSpawn, this, std::placeholders::_1));
    m_pScript->setCallback("spawn_hook", std::bind(&ScriptInterface::cbSpawnHook, this, std::placeholders::_1));
    m_pScript->setCallback("unhook", std::bind(&ScriptInterface::cbUnhook, this, std::placeholders::_1));
    m_pScript->setCallback("pos", std::bind(&ScriptInterface::cbPosition, this, std::placeholders::_1));
    m_pScript->setCallback("vel", std::bind(&ScriptInterface::cbVelocity, this, std::placeholders::_1));
}

ScriptInterface :: ~ScriptInterface()
{
    
}

int ScriptInterface :: cbSpawnHook(lua_State* state)
{
    std::string name = luaL_checkstring(state, 1);
    std::shared_ptr<Object> object;
    if(!(object = m_pFactory->create("data/objects/" + name + ".ini")))
        object = m_pFactory->create("data/backdrops/" + name + ".ini");
    int i = -1;
    assert(object);
    if(object)
    {
        //std::shared_ptr<IScriptable> scriptable = std::dynamic_pointer_cast<IScriptable>(object);
        // following code is O(hell no) -- TODO: fix
        for(i=0;;i++)
            if(m_Hooks.find(i) == m_Hooks.end())
            {
                m_Hooks[i] = std::weak_ptr<IScriptable>(std::dynamic_pointer_cast<IScriptable>(object));
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

int ScriptInterface :: cbSpawn(lua_State* state)
{
    std::string name = luaL_checkstring(state, 1);
    // TODO: keep scripts from accessing filesystem outside of data folder
    if(!m_pFactory->create("data/objects/" + name + ".ini"))
        m_pFactory->create("data/backdrops/" + name + ".ini");
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
    std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state,1))]);
    Object* o = dynamic_cast<Object*>(scriptable.get());
    if(lua_gettop(state) == 3)
    {
        lua_pushnumber(state, o->pos().x);
        lua_pushnumber(state, o->pos().y);
        return 2;
    }
    o->pos(Vector2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3)));
    return 0;
}

int ScriptInterface :: cbVelocity(lua_State* state)
{
    std::shared_ptr<IScriptable> scriptable(m_Hooks[round_int(lua_tonumber(state, 1))]);

    Object* o = dynamic_cast<Object*>(scriptable.get());
    if(lua_gettop(state) == 3)
    {
        lua_pushnumber(state, o->vel().x);
        lua_pushnumber(state, o->vel().y);
        return 2;
    }
    o->vel(Vector2((float)lua_tonumber(state, 2), (float)lua_tonumber(state, 3)));
    return 0;
}

