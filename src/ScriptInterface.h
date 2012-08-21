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
        lua_State* m_pThread; // weak
        std::map<unsigned int, std::weak_ptr<IScriptable>> m_Hooks;
        std::map<std::string, std::function<void()>> m_Callbacks;

    public:

        ScriptInterface(Script* script);
        virtual ~ScriptInterface();

        void setCallback(const char* name, std::function<void()> func);
        static int callback(lua_State* state);
        void call(std::string func_name);

        // callbacks
        void cbSpawnHook();
        void cbHook();
        void cbUnhook();
        void cbSpawn();

        std::shared_ptr<IScriptable> hook(unsigned int id) { 
            std::map<unsigned int, std::weak_ptr<IScriptable>>::iterator itr = m_Hooks.find(id);
            if(itr==m_Hooks.end())
                return nullptr;
            return itr->second.lock();
        }
};

#endif

