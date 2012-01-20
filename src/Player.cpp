#include "Player.h"
#include "Freq.h"
#include "Particle.h"

bool Player :: logic(float t)
{
    const float min_turn_vel = 500.0f;
    const unsigned int turn_frame_time = 100;

    Vector2 old_pos = pos();
    pos() = (Events::get().mousePos() / System::get().scale()) - sprite().size()/2.0f;

    float xvel = (pos().x - old_pos.x) / t; // t will never be 0
    if(xvel > min_turn_vel)
    {
        setImage("right");
        m_FrameResetAlarm.set(Freq::Time(turn_frame_time));
    }
    else if(xvel < -min_turn_vel)
    {
        setImage("left");
        m_FrameResetAlarm.set(Freq::Time(turn_frame_time));
    }
    else
    {
        if(m_FrameResetAlarm.hasElapsed())
            setImage("default");
    }

    if(Events::get().mouse(0) && m_FireRate.hasElapsed())
    {
        std::shared_ptr<Object> bullet(new Particle((std::string)"data/gfx/objects/bullet.png", Vector2(0.0f, -200.0f)));
        bullet->pos() = (pos() + sprite().size()/2.0f) - bullet->sprite().size()/2.0f;
        world()->add(bullet);
        m_FireRate.set(Freq::Time(100));
    }

    Object::logic(t);
    return true;
}

