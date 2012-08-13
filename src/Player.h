#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Object.h"
#include "IControllable.h"
#include "Events.h"
#include "IOwnable.h"
#include "Particle.h"

class Player : public Object, public IControllable, public IOwnable
{
    private:

        void nullify() {
        }

        // unused
        //Vector2 calcVelocity(float t, const Vector2& old_pos) const {
        //    if(floatcmp(t,0.0f))
        //        return Vector2();
        //    return (old_pos - pos()) / t;
        //}
        //void xCollision(std::shared_ptr<Object>& obj);
        
        Freq::Alarm m_FrameResetAlarm;
        Freq::Alarm m_FireRate;
        Freq::Alarm m_SmokeTimer;
        Freq::Alarm m_BlinkTimer;

        int m_MaxHealth;
        int m_Health;

    public:
        Player(const std::string& fn):Object(fn) {
            nullify();
            owner(IOwnable::O_FRIENDLY);
            //sprite().tint(Color(0.0f,0.0f,0.0f,1.0f));
            m_Health = m_MaxHealth = properties().getInt("default","health",1);
        }
        virtual ~Player() {}

        const char* type() const { return "player"; }

        virtual bool logic(float t);
        virtual void render() const {
            Object::render();
        }

        virtual bool solid() const { return true; }
        virtual bool collidable() const { return true; }
        virtual void collisionEvent(std::shared_ptr<Object>& object) {
            Particle* p;
            if(p = dynamic_cast<Particle*>(object.get())) {
                if(p->owner() == IOwnable::O_ENEMY) {
                    m_Health -= p->damage();
                    //p->invalidate();
                }
                return;
            }
            //Enemy* e;
            //if(e = dynamic_cast<Enemy*>(object.get())) {
            //    m_Health -= e->health();
            //    return;
            //}
        }
};

#endif

