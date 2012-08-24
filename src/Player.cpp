#include "Player.h"
#include "Freq.h"
#include "Particle.h"
#include "Log.h"

void Player :: logic(float t)
{
    const float min_turn_vel = 50.0f;
    const unsigned int turn_frame_time = 100;
    
    if(dead())
    {
        invalidate();
        return;
    }

    Vector2 old_pos = pos();
    pos((Events::get().mousePos() / System::get().scale()) - sprite().size()/2.0f);
    
    // bounds just in case (tiled window managers can screw this up)
    if(pos().x < -sprite().size().x/1.0f)
        pos(-sprite().size().x/2.0f, pos().y);
    if(pos().y < -sprite().size().y/2.0f)
        pos(pos().x, -sprite().size().y/2.0f);
    if(pos().x > System::get().w() - sprite().size().x/2.0f)
        pos(System::get().w() - sprite().size().x/2.0f, pos().y);
    if(pos().y > System::get().h() - sprite().size().y/2.0f)
        pos(pos().x, System::get().h() - sprite().size().y/2.0f);

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
        std::shared_ptr<Object> bullet(new Particle((std::string)"bullet.ini"));
        bullet->pos(pos() + sprite().size()/2.0f - bullet->size()/2.0f);
        bullet->vel(Vector2(0.0, -500.0f));
        ((Particle*)bullet.get())->collidable(true);
        ((Particle*)bullet.get())->owner(IOwnable::O_FRIENDLY);
        world()->add(bullet);
        m_FireRate.set(Freq::Time(100));
    }
    else if(Events::get().mouse(1) && m_FireRate.hasElapsed())
    {
        std::shared_ptr<Object> bullet(new Particle((std::string)"rocket.ini"));
        bullet->pos(pos() + sprite().size()/2.0f - bullet->size()/2.0f);
        bullet->vel(Vector2(0.0, -500.0f));
        ((Particle*)bullet.get())->collidable(true);
        ((Particle*)bullet.get())->owner(IOwnable::O_FRIENDLY);
        world()->add(bullet);
        m_FireRate.set(Freq::Time(1000));
    }

    if(m_SmokeTimer.hasElapsed())
    {
        std::shared_ptr<Object> smoke(new Particle(
            (std::string)"trailSmoke.png",
            Freq::Time(100)
        ));
        smoke->pos(pos() + size()/2.0f - smoke->size()/2.0f);
        smoke->pos(Vector2(smoke->pos().x, pos().y + size().y));
        smoke->vel(Vector2(0.1f * (rand() % 1000) * (rand() % 2 ? 1.0f : -1.0f), 0.0f));
        smoke->sprite().depth(10.0f);
        world()->add(smoke);
        m_SmokeTimer.set(Freq::Time(20));
    }

    if(!m_BlinkTimer.hasElapsed() && m_BlinkTimer.remainingTime()/50 % 2)
        sprite().tint(Color(0.5f,0.5f,0.5f,0.5f));
    else
        sprite().untint();

    Object::logic(t);
}

void Player :: render() const
{
    Object::render();
}

void Player :: collisionEvent(std::shared_ptr<Object>& object)
{
    //Particle* p;
    //if(p = dynamic_cast<Particle*>(object.get()))
    //    if(p->owner() == IOwnable::O_ENEMY)
    //        hurt(p->damage());

    if(!object->collidable())
        return;

    IDamaging* d;
    if(m_BlinkTimer.hasElapsed())
        if(d = dynamic_cast<IDamaging*>(object.get())) {
            IOwnable* o = dynamic_cast<IOwnable*>(object.get());
            if(owner() && o->owner() && owner() != o->owner()) {
                m_BlinkTimer.set(Freq::Time(800));
                hurt(d->damage());
            } 
        }
}

