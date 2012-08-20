#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "IScriptable.h"
#include "IFallible.h"

IScriptable :: IScriptable(Script* script)
{
    if(!connect(script))
        throw Failure();
}

bool IScriptable :: connect(Script* script)
{
    return true;
}

