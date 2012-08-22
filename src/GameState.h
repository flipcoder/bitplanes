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
        void nullify() {}

    public:
        GameState() {
            nullify();
            //scoped_dtor<GameState> dtor(this);
            m_spWorld.reset(new World("data/maps/forest.lua"));
            m_spWorld->vel(Vector2(0.0f, -100.0f));// in future: set by world script

            //std::shared_ptr<Object> terrain(new Backdrop("data/terrain/forest.png"));
            std::shared_ptr<Object> player(new Player("plane1.ini"));
            
            //m_spWorld->add(terrain);
            m_spWorld->add(player);

            //for(int i=0; i<20; i++)
            //{
            //    Enemy* e = new Enemy("data/objects/planeE1.ini");
            //    std::shared_ptr<Object> enemy(e);
            //    e->pos(Vector2(e->pos().x, i*-100.0f));
            //    e->vel(Vector2(i*5.0f + 100.0f, 50.0f));
            //    m_spWorld->add(enemy);
            //}
            //dtor.resolve();
        }
        //virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            
            m_spWorld->logic(t);
            
            //if(m_spWorld->done())
            //    return false;

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

