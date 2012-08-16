#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <string>
#include <fstream>
#include "IFallible.h"
#include "IConfigurable.h"
#include "IRealtime.h"
#include "IScriptable.h"
#include <lua.hpp>
#include <luabind/function.hpp>
#include <map>
#include <memory>

class Script : public IFallible, public IConfigurable, public IRealtime
{
    private:
        //std::ifstream m_Script;
        std::vector<std::weak_ptr<IScriptable>> m_Hooks;

    public:
        Script(const std::string& fn);
        virtual ~Script() {}

        virtual bool logic(float t);
        // Load in resources used by script
        void precache();
};

#endif

