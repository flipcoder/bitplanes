#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Player.h"
#include "Backdrop.h"
#include "World.h"
#include "Enemy.h"

class GameState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        std::shared_ptr<Player> m_spPlayer;

    public:
        GameState() {
            m_spWorld.reset(new World("data/maps/road.lua"));
            m_spWorld->vel(Vector2(0.0f, -100.0f));// in future: set by world script

            m_spPlayer.reset(new Player("plane1.ini"));
            
            m_spWorld->add(m_spPlayer);
            //m_spWorld->add(std::dynamic_pointer_cast<Object>(m_spPlayer));
        }
        //virtual ~GameState() {}

        virtual void logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10)) {
                System::get().quit();
                return;
            }
            
            m_spWorld->logic(t);
            
            if(m_spWorld->done())
                System::get().swapState("title");
            if(m_spPlayer->invalid())
                System::get().swapState("title");
        }
        virtual void render() const
        {
            m_spWorld->render();
            //m_spBackdrop->render();
            //m_spPlayer->render();
        }
};

#endif

