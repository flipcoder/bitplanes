#ifndef _SCRIPTINTERFACE_H
#define _SCRIPTINTERFACE_H

#include "IScriptInterface.h"
#include "IScriptable.h"

class Script;

class ScriptInterface : public IScriptInterface
{
    private:
        Script* m_pScript; // weak
        std::vector<std::weak_ptr<IScriptable>> m_Hooks;
    public:
        ScriptInterface(Script* script);
        virtual ~ScriptInterface();
};

#endif

