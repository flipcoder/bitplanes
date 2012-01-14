#ifndef _GAME_STATE_H
#define _GAME_STATE_H

#include "Player.h"

class GameState : public IState
{
    private:

        void nullify() {}

        std::shared_ptr<Image> m_spBackgroundImage;
        std::shared_ptr<Sprite> m_spBackground;
        std::shared_ptr<Player> m_spPlayer;

    public:
        GameState() {
            m_spBackground.reset(new Sprite());
            std::shared_ptr<Image> bg = System::get().imageResources().ensure_shared("data/gfx/backgrounds/forest.png");
            m_spBackground->setImage(bg);

            m_spPlayer.reset(new Player("data/gfx/objects/plane1.ini"));
        }
        virtual ~GameState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            m_spPlayer->logic(t);
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
            m_spBackground->render();
            m_spPlayer->render();
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

