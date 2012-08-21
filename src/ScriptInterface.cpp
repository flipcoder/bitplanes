#include "ScriptInterface.h"
#include "Script.h"

static const char s_unique = '\0'; // addr of this var will be unique across libs

ScriptInterface :: ScriptInterface(Script* script)
{
    assert(script);

    m_pScript = script;
    m_pState = script->state();
    // this didn't work :(
    //m_Functions.push_back(std::bind(&ScriptInterface::spawn, this, std::placeholders::_1));
    //std::cout << *m_Functions.back().target<lua_CFunction>() << std::endl;
    
    lua_register(m_pScript->state(), "spawn", &ScriptInterface::callback);
    //module(m_pScript->state())
    //[
    //    def("spawn_hook", boost::bind(&ScriptInterface::spawnHook, this),
    //    def("spawn", &spawn)
    //];
}

int ScriptInterface :: spawnHook(lua_State* state)
{
    return 0;
}

int ScriptInterface :: spawn(lua_State* state)
{
    std::cout << "hello from lua!" << std::endl;
    return 0;
}

int ScriptInterface :: unhook(lua_State* state)
{
    return 0;
}

ScriptInterface :: ~ScriptInterface()
{
    
}

int ScriptInterface :: callback(lua_State* state)
{
    std::cout << "hello from lua!" << std::endl;
    return 0;
}

