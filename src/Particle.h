#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <memory>
#include "Object.h"

class Particle : public Object
{
    private:
        Vector2 m_vVel;
        void nullify() {}
    public:
        Particle(const std::string& fn, Vector2 vel):
            Object(fn)
        {
            nullify();
            m_vVel = vel;
            sprite().depth(1.0f);
        }
        virtual ~Particle() {}

        virtual bool logic(float t) {
            pos() += (m_vVel - world()->vel()) * t;
            Object::logic(t);
            if(world()->outsideScreen(shared_from_this()))
                invalidate();
        }
        virtual void render() const {
            Object::render();
        }
};

#endif

