#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Player.h"
#include "Terrain.h"

class GameState : public IState
{
    private:

        void nullify() {}

        std::shared_ptr<Terrain> m_spTerrain;
        std::shared_ptr<Player> m_spPlayer;

    public:
        GameState() {
            m_spTerrain.reset(new Terrain("data/gfx/terrain/forest.png"));
            m_spPlayer.reset(new Player("data/gfx/objects/plane1.ini"));
        }
        virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            m_spTerrain->logic(t);
            m_spPlayer->logic(t);
            return true;
        }
        virtual void render() const
        {
            m_spTerrain->render();
            m_spPlayer->render();
        }
};

#endif

