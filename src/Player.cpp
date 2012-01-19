#include "Player.h"
#include "Freq.h"

bool Player :: logic(float t)
{
    const float turn_vel = 500.0f;
    const unsigned int turn_frame_time = 100;
    Vector2 old_pos = pos();
    pos() = (Events::get().mousePos() - sprite().size()/2.0f) / System::get().scale();

    float vel = (pos().x - old_pos.x) / t; // t will never be 0
    if(vel > turn_vel)
    {
        setImage("right");
        m_FrameResetAlarm.set(Freq::Time(turn_frame_time));
    }
    else if(vel < -turn_vel)
    {
        setImage("left");
        m_FrameResetAlarm.set(Freq::Time(turn_frame_time));
    }
    else
    {
        if(m_FrameResetAlarm.hasElapsed())
            setImage("default");
    }

    Object::logic(t);
    return true;
}

