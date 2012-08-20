#ifndef _SCRIPT_H
#define _SCRIPT_H

#include <string>
#include <fstream>
#include "IFallible.h"
#include "IConfigurable.h"
#include "IRealtime.h"
#include "IScriptable.h"
#include "IScriptInterface.h"
#include "Util.h"
#include <lua.hpp>
#include <vector>
#include <memory>

class Script : public IFallible, public IConfigurable, public IRealtime
{
    private:

        std::ifstream m_Script;
        std::vector<std::unique_ptr<IScriptInterface>> m_Interfaces;
        lua_State* m_pState;
        std::string m_Filename;

        void nullify();
        void setupBindings();

    public:

        Script(const std::string& fn);
        virtual ~Script() {
            if(m_pState)
                lua_close(m_pState);
        }

        virtual bool logic(float t) {
            return true;
        }

        bool enable(IScriptInterface* interface);
        bool run();

        // Load in resources used by script
        void precache();

        lua_State* state() { return m_pState; }
};

#endif

