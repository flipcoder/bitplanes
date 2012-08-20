#include "Script.h"
#include "Filesystem.h"
#include "Log.h"
#include "lua.hpp"
#include <luabind/luabind.hpp>
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

bool Script :: run()
{
    return luaL_dofile(m_pState, m_Filename.c_str()) == 0;
}

void Script :: setupBindings()
{
    assert(!m_pState);
    m_pState = lua_open();
    luaopen_base(m_pState);
    luaopen_table(m_pState);
    luaopen_string(m_pState);
    luaopen_math(m_pState);

    //module(m_pState)
    //[
        
    //];
}

