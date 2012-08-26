#ifndef _WORLD_H
#define _WORLD_H

#include "Util.h"
#include "IRealtime.h"
#include "math/vector2.h"
#include "Script.h"
#include "Freq.h"
#include "ObjectFactory.h"
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
        std::unique_ptr<ObjectFactory> m_spFactory;

        // if world locked, new objects will go to spawn list instead of object list (nothing to do with threads)
        bool m_bLocked;
        Vector2 m_vScrollVel;
        std::unique_ptr<Script> m_spScript;
        Freq::Accumulator m_WorldTime;
        unsigned int m_uiWorldTimeMark;

        // assumes AABB is overlapping
        bool pixelCollision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const;

        void nullify() {
            m_bLocked = false;
            m_uiWorldTimeMark = 0;
        }

    public:
        World();
        explicit World(const std::string& fn);

        virtual ~World() {clear();}

        virtual void logic(float t);
        virtual void render() const;

        bool add(std::shared_ptr<Object> obj);
        void clear() {
            m_Objects.clear();
        }
        
        // current screen contain any enemiess
        bool hasEnemies() const;

        bool collision(const Box_t& a, const Box_t& b) const;
        bool collision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const;

        bool outsideScreen(const Box_t& a) const;
        bool outsideScreen(const std::shared_ptr<const Object>& a) const;
        
        bool done() const {
            return m_spScript ? m_spScript->done() : false;
        }
        
        Freq::Accumulator* time() { return &m_WorldTime; }
};

#endif

