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
        std::shared_ptr<Object> bullet(new Particle((std::string)"data/gfx/objects/bullet.png", Vector2(0.0f, -500.0f)));
        bullet->pos() = pos() + sprite().size()/2.0f - bullet->size()/2.0f;
        ((Particle*)bullet.get())->collidable(true);
        bullet->tag("friendly");
        world()->add(bullet);
        m_FireRate.set(Freq::Time(100));
    }
    else if(Events::get().mouse(1) && m_FireRate.hasElapsed())
    {
        std::shared_ptr<Object> bullet(new Particle((std::string)"data/gfx/objects/bulletH.png", Vector2(0.0f, -500.0f)));
        bullet->pos() = pos() + sprite().size()/2.0f - bullet->size()/2.0f;
        ((Particle*)bullet.get())->collidable(true);
        bullet->tag("friendly");
        world()->add(bullet);
        m_FireRate.set(Freq::Time(1000));
    }

    if(m_SmokeTimer.hasElapsed())
    {
        std::shared_ptr<Object> smoke(new Particle(
            (std::string)"data/gfx/objects/trailSmoke.png",
            Vector2(100.0f * (rand() % 1000) * 0.001f * (rand() % 2 ? 1.0f : -1.0f), 50.0f),
            Freq::Time(100))
        );
        smoke->pos() = pos() + size()/2.0f - smoke->size()/2.0f;
        smoke->pos().y = pos().y + size().y;
        smoke->sprite().depth(10.0f);
        world()->add(smoke);
        
        m_SmokeTimer.set(Freq::Time(20));
    }

    Object::logic(t);
    return true;
}

