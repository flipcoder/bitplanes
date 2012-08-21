#ifndef _SCRIPTINTERFACE_H
#define _SCRIPTINTERFACE_H

#include "IScriptInterface.h"
#include "IScriptable.h"
#include "ObjectFactory.h"
#include <map>
#include <functional>

#include <lua.hpp>
#include <boost/any.hpp>

class ObjectFactory;
class Script;

class ScriptInterface : public IScriptInterface
{
    private:
        Script* m_pScript; // weak
        lua_State* m_pState; // weak
        lua_State* m_pThread; // weak
        ObjectFactory* m_pFactory; // weak

        std::map<unsigned int, std::weak_ptr<IScriptable>> m_Hooks;
        std::string test;
    public:
        ScriptInterface(Script* script, ObjectFactory* factory);
        virtual ~ScriptInterface();
        
        // callbacks
        int cbSpawnHook(lua_State* state);
        //void cbHook();
        int cbUnhook(lua_State* state);
        int cbSpawn(lua_State* state);
        int cbPosition(lua_State* state);
        int cbVelocity(lua_State* state);

        std::shared_ptr<IScriptable> hook(unsigned int id) { 
            std::map<unsigned int, std::weak_ptr<IScriptable>>::iterator itr = m_Hooks.find(id);
            if(itr==m_Hooks.end())
                return nullptr;
            return itr->second.lock();
        }
};

#endif

