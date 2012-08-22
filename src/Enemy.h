#ifndef _ENEMY_H
#define _ENEMY_H

#include <memory>
#include <boost/optional/optional.hpp>
#include "math/vector2.h"
#include "Object.h"
#include "Freq.h"
#include "Events.h"
#include "Particle.h"
#include "Log.h"
#include "Util.h"
#include "IDamaging.h"
#include "IDestroyable.h"
#include "IScriptable.h"

class Enemy : public Object, public IOwnable, public IDamaging, public IDestroyable, public IScriptable
{
    private:
        void nullify() {
        }

        Freq::Alarm m_SmokeTimer;
        boost::optional<Freq::Alarm> m_FlashTimer;

    public:
        Enemy(const std::string& fn):
            Object(fn),
            IDestroyable(properties().getInt("default","health",1)),
            IDamaging(properties().getInt("default","damage",1))
        {
            nullify();
            //scoped_dtor<Enemy> dtor; // code below probably won't throw but just in case
            sprite().depth(properties().getFloat("default", "depth", -50.0f));
            owner(IOwnable::O_ENEMY);

            /// start centered, above screen by default
            pos(Vector2(System::get().w()/2.0f - size().x/2.0f, -size().y));

            // set default speed from config file
            float speed;
            if(properties().getFloatValue("default", "speed", speed)) {
                vel(Vector2(vel().x, speed));
            }
            //dtor.resolve();
        }
        virtual ~Enemy() {
            // TODO: If you add anything here, make sure you put back in scoped_dtors
        }

        virtual bool logic(float t) {
            //move((m_vVel - world()->vel()) * t);
            Object::logic(t);
            //if(world()->outsideScreen(shared_from_this())) {
            if(pos().x < -size().x/2.0f) {
                vel(Vector2(std::fabs(vel().x), vel().y));
                pos(Vector2(-size().x/2.0f, pos().y));
            }else if (pos().x > System::get().w()-size().x/2.0f) {
                vel(Vector2(-std::fabs(vel().x), vel().y));
                pos(Vector2(System::get().w()-size().x/2.0f, pos().y));
            }

            if(pos().y < 0.0f && vel().y < 0.0f)
                invalidate();
            if(pos().y > System::get().h())
                invalidate();

            if(m_FlashTimer && m_FlashTimer->hasElapsed()) {
                sprite().untint();
                m_FlashTimer = boost::optional<Freq::Alarm>();

                if(dead())
                    invalidate();
            }

            if(m_SmokeTimer.hasElapsed())
            {
                std::shared_ptr<Object> smoke(new Particle(
                    (std::string)"trailSmoke.png",
                    Freq::Time(100)
                ));
                smoke->pos(pos() + size()/2.0f - smoke->size()/2.0f);
                smoke->pos(Vector2(smoke->pos().x, pos().y));
                smoke->vel(Vector2(0.1f * (rand() % 1000) * (rand() % 2 ? 1.0f : -1.0f), 0.0f));
                smoke->sprite().depth(10.0f);
                world()->add(smoke);
                m_SmokeTimer.set(Freq::Time(20));
            }

            return true;
        }
        //virtual void render() const {
        //    Object::render();
        //}
        
        virtual bool solid() const { return true; }
        virtual bool collidable() const { return true; }
        virtual void collisionEvent(std::shared_ptr<Object>& object) {
            Particle* p;
            if(p = dynamic_cast<Particle*>(object.get())) {
                if(p->owner() == IOwnable::O_FRIENDLY) {
                    hurt(p->damage());
                    p->invalidate();
                    m_FlashTimer = Freq::Alarm(Freq::Time(50));
                    sprite().tint(Color(0.5f,0.5f,0.5f,0.5f));
                }
            }
        }
};

#endif


