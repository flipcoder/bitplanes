#include "Script.h"
#include "Filesystem.h"
#include "Log.h"
#include <lua.hpp>
//#include <luabind/luabind.hpp>
#include "Freq.h"

Script :: Script(const std::string& fn):
    IConfigurable(fn)
{
    nullify();
    scoped_dtor<Script> dtor(this);
    
    // attempt to get script filename from ini file
    if(Filesystem::hasExtension(fn,"ini"))
    {
        properties().getStringValue("default", "script", m_Filename);
        if(!m_Filename.empty())
        {
            Log::get().error("Could not locate script property in file \"" + fn + "\"");
            throw Failure();
        }
    }
    else
        m_Filename = fn; // use passed in filename as script filename

    //m_Script.open(script_fn);
    //if(m_Script.bad())
    //{
    //    Log::get().error((std::string)"Unable to open script \"" + script_fn + "\"");
    //    throw Failure();
    //}

    setupBindings();
    m_TickFreq = 60;
    //m_TickTime.speed(1000.0f);

    dtor.resolve();
}

void Script :: nullify()
{
    m_pState = NULL;
    m_bDone = false;
    m_TickFreq = 0;
    m_SleepFrames = 0;
}

void Script :: precache()
{
    // precache resources used by script
}

bool Script :: enable(IScriptInterface* interface)
{
    m_Interfaces.push_back(std::unique_ptr<IScriptInterface>(interface));
    return true;
}

bool Script :: reset()
{
    m_pThread = lua_newthread(m_pState);
    return luaL_loadfile(m_pThread, m_Filename.c_str()) == 0;
}

void Script :: setupBindings()
{
    assert(!m_pState);
    m_pState = lua_open();
    luaopen_base(m_pState);
    luaopen_table(m_pState);
    //luaopen_io(m_pState);
    luaopen_string(m_pState);
    luaopen_math(m_pState);
    //luaopen_libs(m_pState);
}

void Script :: logic(float t)
{
    // accumualate time
    m_TickTime.logic(t);
    if(m_TickTime.milliseconds() < round_int(1000.0f / m_TickFreq))
        return;
    m_TickTime.reset();

    // need to sleep?
    if(m_SleepFrames > 0)
    {
        // sleep this frame
        m_SleepFrames -= 1;
        return;
    }

    int status = lua_resume(m_pThread, 0);
    if(status != LUA_YIELD)
    {
        // either error or done with script
        if(status == LUA_ERRRUN && lua_isstring(m_pThread, -1))
        {
            Log::get().error(str(lua_tostring(m_pThread, -1)));
            return; // bail
        }
        else
        {
            // script is finished
            m_bDone = true;
        }
    }
    
    // figure out how many frames to sleep before resuming script
    if(lua_isnumber(m_pThread, 1))
    {
        m_SleepFrames = round_int(lua_tonumber(m_pThread, 1) - 1.0);
        if(m_SleepFrames < 0)
            m_SleepFrames = 0;
    }
}

int Script :: call(lua_State* state, std::string func_name)
{
    return m_Callbacks[func_name](state);
}

void Script :: setCallback(const char* name, std::function<int(lua_State*)> func)
{
    m_Callbacks[name] = func;
    lua_pushlightuserdata(m_pState, (void*)this);
    lua_pushstring(m_pState, name);
    lua_pushcclosure(m_pState, &Script::callback, 2);
    lua_setglobal(m_pState, name);
}

int Script :: callback(lua_State* state)
{
    //lua_pushlightuserdata(state, (void*)&s_unique);
    //lua_gettable(state, LUA_REGISTRYINDEX);
    Script* script = (Script*)lua_touserdata(state, lua_upvalueindex(1));
    assert(script);
    return script->call(state, lua_tostring(state, lua_upvalueindex(2)));
}

