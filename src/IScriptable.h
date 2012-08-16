#include <iostream>
#include "Util.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "ICloneable.h"

class IScriptable : public ICloneable
{
    private:
        
    public:

        IScriptable();
        virtual ~IScriptable();
};

