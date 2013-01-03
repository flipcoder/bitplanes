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
class World;

class ScriptInterface : public IScriptInterface
{
    private:
        Script* m_pScript; // weak
        lua_State* m_pState; // weak
        lua_State* m_pThread; // weak
        ObjectFactory* m_pFactory; // weak
        World* m_pWorld; //weak

        std::map<unsigned int, std::vector<std::weak_ptr<IScriptable>>> m_Hooks;
    public:
        ScriptInterface(Script* script, World* world, ObjectFactory* factory);
        virtual ~ScriptInterface();
        
        // callbacks
        
        // TODO: add type-specific spawn()s
        //  .ini names are getting too similar
        //  ex: enemy("planeE1")
        int cbSpawnHook(lua_State* state, std::string type);
        //int cbHookEnemies(lua_State* state);
        //void cbHook();
        int cbUnhook(lua_State* state);
        int cbUnhookAll(lua_State* state);
        int cbSpawn(lua_State* state, std::string type);
        int cbPosition(lua_State* state);
        int cbCenter(lua_State* state);
        int cbVelocity(lua_State* state);
        int cbSize(lua_State* state);
        int cbHealth(lua_State* state);
        int cbMaxHealth(lua_State* state);
        int cbDepth(lua_State* state);
        int cbClear(lua_State* state);
        int cbExists(lua_State* state);
        int cbEnemies(lua_State* state);
        int cbPlayers(lua_State* state);
        int cbMusic(lua_State* state);
        int cbConfig(lua_State* state);
        
        //std::shared_ptr<IScriptable> hook(unsigned int id) { 
        //    std::map<unsigned int, std::weak_ptr<IScriptable>>::iterator itr = m_Hooks.find(id);
        //    if(itr==m_Hooks.end())
        //        return nullptr;
        //    return itr->second.lock();
        //}
        
        // get a list of scriptable objects for the given identifier
        std::vector<std::shared_ptr<IScriptable>> hook(unsigned int id) {
            if(m_Hooks.find(id) == m_Hooks.end())
                return std::vector<std::shared_ptr<IScriptable>>();

            auto& hooks = m_Hooks[id];
            std::vector<std::shared_ptr<IScriptable>> ret;
            ret.reserve(hooks.size());
            foreach(auto& hook, hooks) {
                try{
                    std::shared_ptr<IScriptable> test_hook(hook);
                    ret.push_back(hook.lock());
                }catch(std::bad_weak_ptr&) {}
            }
            return ret;
        }

        // TODO: do this without invalidating iterators
        //void flush() {
        //    for(auto itr = m_Hooks.begin();
        //        itr != m_Hooks.end();
        //        ++itr)
        //    {
                
        //    }
        //}
        
        // removes all invalid hooks for the given indentifier
        // also, returns hook count
        int flush(unsigned int id) {
            int count = 0;
            if(m_Hooks.find(id) == m_Hooks.end())
                return 0;
            auto& hooks = m_Hooks[id];
            for(auto itr = hooks.begin();
                itr != hooks.end();) {
                //try{
                //    std::shared_ptr<IScriptable> test_hook(*itr);
                //    ++itr;
                //    ++count;
                //}catch(const std::bad_weak_ptr&) {
                    if(itr->expired())
                        itr = hooks.erase(itr);
                    else
                        ++itr;
                //}
            }
            if(hooks.empty())
                m_Hooks.erase(id);
            return count;
        }

        //unsigned int combine(unsigned int id, unsigned int id) {
        //    return 0;
        //}
        
        // TODO: seperate object spawns (backdrop, particle, item, enemy, etc.)
        //  and searching functions for each
        // Example: local all_particles = particles()
        
        // Node Types:
        //  sound (attach to IMovable?)
        //  music
        //  enemy
        //  backdrop
        //  item
        //  particle/custom
        //  zone(?) -- specific non-renderable shapes probably not needed

        // TODO: assigning scripts to objects
        // TODO: groupings: add/intersect, combine/union, remove/subtract
        // TODO: triggers/events
        // TODO: generator?
        // TODO: script(object, filename) -- assign a script
        // TODO: filter functions with predicates? + each()/generators?
};

#endif

