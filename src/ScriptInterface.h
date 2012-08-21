#ifndef _SCRIPTINTERFACE_H
#define _SCRIPTINTERFACE_H

#include "IScriptInterface.h"
#include "IScriptable.h"
#include <map>
#include <functional>

#include <lua.hpp>
#include <boost/any.hpp>

class Script;

class ScriptInterface : public IScriptInterface
{
    private:
        Script* m_pScript; // weak
        lua_State* m_pState; // weak
        std::map<unsigned int, std::weak_ptr<IScriptable>> m_Hooks;
        std::vector<std::function<int(lua_State*)>> m_Functions;
    public:
        ScriptInterface(Script* script);
        virtual ~ScriptInterface();

        static int callback(lua_State* state);

        int spawnHook(lua_State* state);
        int unhook(lua_State* state);
        int spawn(lua_State* state);
};

#endif

