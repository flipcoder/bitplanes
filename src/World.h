#ifndef _WORLD_H
#define _WORLD_H

#include "Util.h"
#include "IRealtime.h"
#include "math/vector2.h"

class Object;
class World : public IRealtime
{
    private:
        std::list<std::shared_ptr<Object>> m_Objects;
        std::list<std::shared_ptr<Object>> m_SpawnList;

        // if world locked, new objects will go to spawn list instead of object list (nothing to do with threads)
        bool m_bLocked;

        void nullify() {
            m_bLocked = false;
        }

        Vector2 m_vScrollVel;

    public:
        World() {
            nullify();
        }
        virtual ~World() {clear();}

        virtual bool logic(float t);
        virtual void render() const;

        bool add(std::shared_ptr<Object>& obj);
        void clear() {
            m_Objects.clear();
        }

        const Vector2 scrollVel() const { return m_vScrollVel; }
        Vector2 scrollVel() { return m_vScrollVel; }
        void scrollVel(Vector2 s) { m_vScrollVel = s; }
};

#endif

