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
        
        Freq::Alarm m_FrameResetAlarm;
        Freq::Alarm m_FireRate;
        Freq::Alarm m_SmokeTimer;

    public:
        Player(const std::string& fn):Object(fn) {
            nullify();
        }
        virtual ~Player() {}

        virtual bool logic(float t);
        virtual void render() const {
            Object::render();
        }
};

#endif

