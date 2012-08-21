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
    dtor.resolve();
}

void Script :: nullify()
{
    m_pState = NULL;
    m_bDone = false;
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

    //module(m_pState)
    //[
        
    //];
}

bool Script :: logic(float t)
{
    // accumualate time
    m_TickTime.logic(round_int(t*1000.0f));
    if(m_TickTime.mark() < 1000)
        return true;
    m_TickTime.reset();
    
    int status = lua_resume(m_pThread, 0);
    if(status != LUA_YIELD)
    {
        // either error or done with script
        if(status == LUA_ERRRUN && lua_isstring(m_pThread, -1))
        {
            Log::get().error(str(lua_tostring(m_pThread, -1)));
            return false; // bail
        }
        else
        {
            // script is finished
            m_bDone = true;
        }
    }
}

