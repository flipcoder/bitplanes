#include "Script.h"
#include "Filesystem.h"
#include "Log.h"

Script :: Script(const std::string& fn):
    IConfigurable(fn)
{
    //scoped_dtor<Script> dtor(this);
    std::string script_fn;
    
    // attempt to get script filename from ini file
    if(Filesystem::hasExtension(fn,"ini"))
    {
        properties().getStringValue("default", "script", script_fn);
        if(!script_fn.empty())
        {
            Log::get().error("Could not locate script property in file \"" + fn + "\"");
            throw Failure();
        }
    }
    else if (Filesystem::hasExtension(fn, "lua"))
        script_fn = fn; // use passed in filename as script filename
    else
    {
        Log::get().error((std::string)"Unable to locate script \"" + script_fn + "\"");
        throw Failure();
    }

    //m_Script.open(script_fn);
    //if(m_Script.bad())
    //{
    //    Log::get().error((std::string)"Unable to open script \"" + script_fn + "\"");
    //    throw Failure();
    //}
    
    //dtor.resolve();
}

bool Script :: logic(float t)
{
    
}
        

void Script :: precache()
{
    // precache resources used by script
}

