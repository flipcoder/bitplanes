#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Plane.h"

class GameState : public IState
{
    private:

        void nullify() {}

        //std::shared_ptr<Sprite> m_spBackground;
        std::shared_ptr<Plane> m_spPlane;

    public:
        GameState() {
            m_spPlane.reset(new Plane("data/gfx/objects/plane1.ini"));
            //m_spBackground.reset(Sprite::load("data/gfx/backgrounds/forest.png"));
            //if(!m_spBackground.get() || m_spBackground.get()->hasError())
            //    setError(m_spBackground.get()->getError());
            //m_spPlane.reset(Sprite::load("data/gfx/objects/plane1.png"));
            //if(!m_spPlane.get() || m_spPlane.get()->hasError())
            //    setError(m_spPlane.get()->getError());
            //m_spPlane->pos() = Vector2(100.0f, 100.0f);
            //m_spPlane->vel() = Vector2(0.1f, 0.1f);
            //m_spBackground->vel() = Vector2(0.0f, 80.0f);
        }
        virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            //if(Events::get().key(ALLEGRO_KEY_ESCAPE))
            //    return false;

            //const float speed = 100.0f;
            
            //m_spPlane->vel() = Vector2();

            //if(Events::get().key(ALLEGRO_KEY_UP))
            //    m_spPlane->vel().y = -speed;
            //if(Events::get().key(ALLEGRO_KEY_DOWN))
            //    m_spPlane->vel().y = speed;
            //if(Events::get().key(ALLEGRO_KEY_LEFT))
            //    m_spPlane->vel().x = -speed;
            //if(Events::get().key(ALLEGRO_KEY_RIGHT))
            //    m_spPlane->vel().x = speed;

            //m_spPlane->pos() += (m_spPlane->vel() * t);
            //m_spBackground->pos() += (m_spBackground->vel() * t);
            //while(m_spBackground->pos().y > 0.0f)
            //    m_spBackground->pos().y -= m_spBackground->h();
            //return true;
            return true;
        }
        virtual void render() const
        {
            //float old_y = m_spBackground->pos().y;

            //m_spBackground->render();
            //for(int i=0; i<2; i++)
            //{
            //    m_spBackground->pos().y += m_spBackground->h();
            //    m_spBackground->render();
            //}
            //m_spBackground->pos().y = old_y;

            //m_spPlane->render();
        }
};

#endif

