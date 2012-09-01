#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Object.h"
#include "IControllable.h"
#include "Events.h"
#include "IOwnable.h"
#include "Particle.h"
#include "IDestroyable.h"
#include "IDamaging.h"
#include "Audio.h"
#include "IStats.h"

class Player :
    public Object,
    public IControllable,
    public IOwnable,
    public IDestroyable,
    public IDamaging,
    public IStats
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
        
        std::shared_ptr<Audio::Sound> m_spSound;
        std::weak_ptr<Client> m_wpClient;
        
        bool m_bCalledInit;
       
    public:
        Player(const std::string& fn, std::shared_ptr<Client> client):
            Object(fn),
            IDestroyable(properties().getInt("default","health",1)),
            IDamaging(properties().getInt("default","damage",1)),
            IStats(client)
        {
            nullify();
            owner(IOwnable::O_FRIENDLY);
            //sprite().tint(Color(0.0f,0.0f,0.0f,1.0f));
        }
        virtual ~Player() {}

        virtual void onAdd() {
            std::string sound;
            if(properties().getStringValue("sounds","spawn",sound)) {
                m_spSound.reset(new Audio::Sound(sound));
                m_spSound->play();
                m_spSound->pos(pos());
                Audio::get().listen(m_spSound);
            }
            m_FrameResetAlarm.timer(world()->time());
            m_FireRate.timer(world()->time());
            m_SmokeTimer.timer(world()->time());
            m_BlinkTimer.timer(world()->time());
        }

        const char* type() const { return "player"; }

        virtual void logic(float t);
        virtual void render() const;
        
        virtual bool solid() const { return true; }
        virtual bool collidable() const { return m_BlinkTimer.hasElapsed(); }

        virtual void collisionEvent(std::shared_ptr<Object>& object);
        
        // may be null (if client invalid/disconnected, etc.)
        std::shared_ptr<Client> client() {
            return m_wpClient.lock();
        }
};

#endif

