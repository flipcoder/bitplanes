#include "Script.h"
#include "FileSystem.h"

Script :: Script(const std::string& fn):
    IConfigurable(fn)
{
    //scoped_dtor<Script> dtor(this);
    std::string script_fn;
    
    // attempt to get script filename from ini file
    if(FileSystem::hasExtension(fn,"ini"))
    {
        properties().getStringValue("default", "script", script_fn);
        if(!script_fn.empty())
        {
            setError("Could not locate script property in file \"" + fn + "\"");
            throw Failure();
        }
    }
    else
        script_fn = fn; // use passed in filename as script filename

    m_Script.open(script_fn);
    if(m_Script.bad())
    {
        setError("Unable to open script \"" + script_fn + "\"");
        throw Failure();
    }
    //dtor.resolve();
}

void Script :: precache()
{
    // precache resources used by script
}

