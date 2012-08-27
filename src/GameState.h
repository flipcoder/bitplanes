#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Player.h"
#include "Backdrop.h"
#include "World.h"
#include "Enemy.h"
#include "Freq.h"
#include <boost/optional.hpp>

class GameState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        std::shared_ptr<Player> m_spPlayer;
        boost::optional<Freq::Alarm> m_aAfterDeath;
        //std::shared_ptr<Audio::Sound> m_spReviveSound;

    public:
        GameState() {
            m_spWorld.reset(new World("data/maps/road.lua"));

            m_spPlayer.reset(new Player("plane1.ini"));
            m_spWorld->add(m_spPlayer);

        //    m_spReviveSound.reset(new Audio::Sound("revive.wav"));
        //    m_spReviveSound->play();
        }
        //virtual ~GameState() {}

        virtual void logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10)) {
                System::get().quit();
                return;
            }
            
            m_spWorld->logic(t);
            
            // replace with some sort of mode state logic
            if(m_spWorld->done())
                System::get().swapState("title");

            if(m_aAfterDeath)
            {
                if(m_aAfterDeath->hasElapsed())
                    System::get().swapState("game"); // restart
            }
            else if(m_spPlayer->invalid())
            {
                m_aAfterDeath = Freq::Alarm(Freq::Time(1000));
            }
        }
        virtual void render() const
        {
            m_spWorld->render();
            //m_spBackdrop->render();
            //m_spPlayer->render();
        }
};

#endif

