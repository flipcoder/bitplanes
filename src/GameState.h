#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Player.h"
#include "Terrain.h"
#include "World.h"

class GameState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        void nullify() {}

    public:
        GameState() {
            nullify();
            m_spWorld.reset(new World());
            m_spWorld->vel(Vector2(0.0f, -100.0f));

            std::shared_ptr<Object> terrain;
            std::shared_ptr<Object> player;
            
            terrain.reset(new Terrain("data/gfx/terrain/forest.png"));
            player.reset(new Player("data/gfx/objects/plane1.ini"));

            m_spWorld->add(terrain);
            m_spWorld->add(player);
        }
        virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            
            m_spWorld->logic(t);
            return true;
        }
        virtual void render() const
        {
            m_spWorld->render();
            //m_spTerrain->render();
            //m_spPlayer->render();
        }
};

#endif

