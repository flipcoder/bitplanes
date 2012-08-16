#ifndef _ISCRIPTABLE_H
#define _ISCRIPTABLE_H

#include <iostream>
#include "Util.h"
#include <lua.hpp>
#include <luabind/luabind.hpp>
#include "IFallible.h"
//#include "ICloneable.h"

class Script;
class IScriptable/*: public ICloneable, public IFallible*/
{
    private:

        Script* m_script; //weak
        
    public:

        IScriptable(Script* script = nullptr);
        virtual ~IScriptable() {}

        bool connect(Script* script);
};

#endif
