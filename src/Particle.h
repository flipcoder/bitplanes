#ifndef _PARTICLE_H
#define _PARTICLE_H

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
        }
        virtual ~Particle() {}

        virtual bool logic(float t) {
            pos() += (m_vVel * t);
            Object::logic(t);
        }
        virtual void render() const {
            Object::render();
        }
};

#endif

