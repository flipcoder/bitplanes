#ifndef _WORLD_H
#define _WORLD_H

#include "Util.h"
#include "IRealtime.h"
#include "math/vector2.h"
#include "Script.h"
#include "Freq.h"

class Object;
class World : public IRealtime
{
    private:

        struct Box_t
        {
            int x,y,w,h;
            Box_t() {
                //x=y=w=h=0;
            }
            Box_t(int x, int y, int w, int h) {
                this->x=x;
                this->y=y;
                this->w=w;
                this->h=h;
            }
            void set(int x, int y, int w, int h) {
                this->x=x;
                this->y=y;
                this->w=w;
                this->h=h;
            }
        };

        std::list<std::shared_ptr<Object>> m_Objects;
        std::list<std::shared_ptr<Object>> m_SpawnList;

        // if world locked, new objects will go to spawn list instead of object list (nothing to do with threads)
        bool m_bLocked;
        Vector2 m_vScrollVel;

        void nullify() {
            m_bLocked = false;
        }

        std::shared_ptr<Script> m_spScript;
        Freq::Accumulator m_WorldTime;

        // assumes AABB is overlapping
        bool pixelCollision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const;


    public:
        World() {
            nullify();
        }
        virtual ~World() {clear();}

        virtual bool logic(float t);
        virtual void render() const;

        bool openScript(const std::string& fn) {
            
        }
        bool add(std::shared_ptr<Object>& obj);
        void clear() {
            m_Objects.clear();
        }

        const Vector2 vel() const { return m_vScrollVel; }
        Vector2 vel() { return m_vScrollVel; }
        void vel(Vector2 s) { m_vScrollVel = s; }

        bool collision(const Box_t& a, const Box_t& b) const;
        bool collision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const;

        bool outsideScreen(const Box_t& a) const;
        bool outsideScreen(const std::shared_ptr<const Object>& a) const;

};

#endif

