#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <memory>
#include "Object.h"
#include "Freq.h"
#include "IOwnable.h"
#include <boost/optional/optional.hpp>
#include "IDamaging.h"
#include "Audio.h"

class Particle:
    public Object,
    public IOwnable,
    public IDamaging,
    public IScriptable
{
    private:

        bool m_bCollidable;
        void nullify() {
            m_bCollidable = false;
            m_bCalledInit = false;
        }

        boost::optional<std::pair<float,float>> m_Life;
        std::shared_ptr<Audio::Sound> m_spSound;

        bool m_bCalledInit;
    public:
        Particle(const std::string& fn, boost::optional<Freq::Time> life = boost::optional<Freq::Time>()):
            Object(fn),
            IDamaging(properties().getInt("default", "damage", 0))
        {
            nullify();
            if(life)
                m_Life = std::pair<float,float>(life->get(),life->get());
            else
            {
                float expiry = properties().getFloat("default","expiry",-1.0f);
                if(expiry > 0.0f)
                    m_Life = std::pair<float,float>(expiry, expiry);
            }
            sprite().depth(1.0f);

            if(damage() > 0)
                m_bCollidable = true;
        }
        virtual ~Particle() {}
        
        virtual void onInit() {
            std::string sound;
            if(properties().getStringValue("sounds","spawn",sound)) {
                m_spSound.reset(new Audio::Sound(sound));
                m_spSound->play();
                m_spSound->pos(pos());
                Audio::get().listen(m_spSound);
            }
        }

        //virtual void onCollision() {
        //    std::string sound;
        //    if(properties().getStringValue("sounds","collision",sound)) {
        //        m_spSound.reset(new Audio::Sound(sound));
        //        m_spSound->play();
        //        m_spSound->pos(pos());
        //        Audio::get().listen(m_spSound);
        //    }
        //}

        //virtual void onDeath() {
        //}

        virtual void logic(float t) {
            if(!m_bCalledInit) {
                onInit();
                m_bCalledInit = true;
            }

            if(m_spSound)
                m_spSound->pos(pos());

            //move((m_vVel - world()->vel()) * t);
            if(m_Life) {
                m_Life->first -= Freq::Time::seconds(t).get();
                //if(m_Life->first > m_Life->second) {
                if(m_Life->first <= 0.0f) {
                    invalidate();
                    return;
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
        }
        virtual void render() const {
            Object::render();
        }

        virtual bool solid() const { return false; }
        virtual bool collidable() const { return m_bCollidable; }
        void collidable(bool b) { m_bCollidable = b; }

        virtual void collisionEvent(std::shared_ptr<Object>& object);

        const char* type() const { return "particle"; }
};

#endif

