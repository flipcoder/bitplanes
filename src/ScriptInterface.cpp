#include "ScriptInterface.h"
#include "Script.h"

static const char s_unique = '\0'; // addr of this var will be unique across libs

ScriptInterface :: ScriptInterface(Script* script)
{
    assert(script);

    m_pScript = script;
    m_pState = script->state();
    m_pThread = script->thread();
    
    // this didn't work :(
    //m_Functions.push_back(std::bind(&ScriptInterface::spawn, this, std::placeholders::_1));
    //std::cout << *m_Functions.back().target<lua_CFunction>() << std::endl;
    
    lua_pushlightuserdata(m_pState, (void*)&s_unique);
    lua_pushlightuserdata(m_pState, (void*)this);
    lua_settable(m_pState, LUA_REGISTRYINDEX);
    
    setCallback("spawn", std::bind(&ScriptInterface::cbSpawn, this));
    setCallback("spawn_hook", std::bind(&ScriptInterface::cbSpawnHook, this));
    setCallback("unhook", std::bind(&ScriptInterface::cbUnhook, this));
}

void ScriptInterface :: call(std::string func_name)
{
    std::cout << "calling method: " << func_name << std::endl;
    m_Callbacks[func_name]();
}

void ScriptInterface :: cbSpawnHook()
{
}

void ScriptInterface :: cbSpawn()
{
}

void ScriptInterface :: cbUnhook()
{
}

void ScriptInterface :: setCallback(const char* name, std::function<void()> func)
{
    m_Callbacks[name] = func;
    lua_pushstring(m_pState, name);
    lua_pushcclosure(m_pState, &ScriptInterface::callback, 1);
    lua_setglobal(m_pState, name);
}

ScriptInterface :: ~ScriptInterface()
{
    
}

int ScriptInterface :: callback(lua_State* state)
{
    lua_pushlightuserdata(state, (void*)&s_unique);
    lua_gettable(state, LUA_REGISTRYINDEX);
    ScriptInterface* interface = (ScriptInterface*)lua_touserdata(state, -1);
    assert(interface);
    interface->call(lua_tostring(state, lua_upvalueindex(1)));
    return 0;
}

