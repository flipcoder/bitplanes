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

    public:
        GameState() {
            m_spWorld.reset(new World("data/maps/forest.lua"));
            m_spWorld->vel(Vector2(0.0f, -100.0f));// in future: set by world script

            std::shared_ptr<Object> player(new Player("plane1.ini"));
            m_spWorld->add(player);
        }
        //virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            
            m_spWorld->logic(t);
            
            if(m_spWorld->done())
                return false;

            return true;
        }
        virtual void render() const
        {
            m_spWorld->render();
            //m_spBackdrop->render();
            //m_spPlayer->render();
        }
};

#endif

