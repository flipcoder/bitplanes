#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Object.h"
#include "IControllable.h"
#include "Events.h"

class Player : public Object, public IControllable
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

    public:
        Player(const std::string& fn):Object(fn) {
            nullify();
            //sprite().tint(Color(0.0f,0.0f,0.0f,1.0f));
        }
        virtual ~Player() {}

        const char* type() const { return "player"; }

        virtual bool logic(float t);
        virtual void render() const {
            Object::render();
        }
        virtual bool collidable() { return true; }
        //virtual bool solid() { return true; }
        virtual void collisionEvent(std::shared_ptr<Object>& object) {}
};

#endif

