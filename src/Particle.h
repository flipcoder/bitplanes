#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <memory>
#include "Object.h"
#include "Freq.h"
#include <boost/optional/optional.hpp>

class Particle : public Object
{
    private:

        bool m_bCollidable;
        Vector2 m_vVel;
        void nullify() {
            m_bCollidable = false;
        }

        boost::optional<std::pair<float,float>> m_Life;

    public:
        Particle(const std::string& fn, Vector2 vel, boost::optional<Freq::Time> life = boost::optional<Freq::Time>()):
            Object(fn)
        {
            nullify();
            if(life)
                m_Life = std::pair<float,float>(life->get(),life->get());
            m_vVel = vel;
            sprite().depth(1.0f);
        }
        virtual ~Particle() {}

        virtual bool logic(float t) {
            pos() += (m_vVel - world()->vel()) * t;
            if(m_Life) {
                m_Life->first -= Freq::Time::seconds(t).get();
                //if(m_Life->first > m_Life->second) {
                if(m_Life->first <= 0.0f) {
                    invalidate();
                    return true;
                }

                //if(!sprite().tint())
                //    sprite().tint(Color());
                //Color c = *sprite().tint();
                //c.a = (1.0f - m_Life->first)/ m_Life->second;
                //sprite().tint(c);
            }
            Object::logic(t);
            if(world()->outsideScreen(shared_from_this()))
                invalidate();

            return true;
        }
        virtual void render() const {
            Object::render();
        }
        virtual bool collidable() { return m_bCollidable; }
        void collidable(bool b) { m_bCollidable = b; }
};

#endif

