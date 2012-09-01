#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include <boost/optional.hpp>
#include "Player.h"
#include "Backdrop.h"
#include "World.h"
#include "Enemy.h"
#include "Freq.h"
#include "Session.h"

class GameState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        //std::shared_ptr<Player> m_spPlayer;
        std::vector<std::shared_ptr<Player>> m_Players;
        boost::optional<Freq::Alarm> m_aAfterDeath;
        Freq::Accumulator m_GameTime;

    public:
        
        GameState();
        virtual ~GameState();

        bool playersDead() const;
        virtual void logic(float t);
        virtual void render() const {
            m_spWorld->render();
        }
};

#endif

