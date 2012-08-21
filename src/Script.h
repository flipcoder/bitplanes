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
#include "Freq.h"

class Script : public IFallible, public IConfigurable, public IRealtime
{
    private:

        std::ifstream m_Script;
        std::vector<std::unique_ptr<IScriptInterface>> m_Interfaces;
        lua_State* m_pState;
        lua_State* m_pThread;
        std::string m_Filename;
        unsigned int m_TickFreq;

        void nullify();
        void setupBindings();
        
        Freq::Accumulator m_TickTime;

        bool m_bDone;

    public:

        Script(const std::string& fn);
        virtual ~Script() {
            if(m_pState)
                lua_close(m_pState);
        }

        virtual bool logic(float t);

        bool enable(IScriptInterface* interface);
        bool reset();

        // Load in resources used by script
        void precache();

        lua_State* state() { return m_pState; }
        lua_State* thread() { return m_pThread; }

        bool done() const { return m_bDone; }
};

#endif

