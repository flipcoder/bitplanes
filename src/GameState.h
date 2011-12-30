#ifndef _GAME_STATE_H
#define _GAME_STATE_H

class GameState : public IRealtime
{
    private:

        void nullify() {}

        std::shared_ptr<Sprite> m_spBackground;
        std::shared_ptr<Sprite> m_spPlane;

    public:
        GameState() {
            m_spBackground.reset(Sprite::load("data/gfx/backgrounds/forest.png"));
            if(!m_spBackground.get() || m_spBackground.get()->hasError())
                setError(m_spBackground.get()->getError());
            m_spPlane.reset(Sprite::load("data/gfx/objects/plane1.png"));
            if(!m_spPlane.get() || m_spPlane.get()->hasError())
                setError(m_spPlane.get()->getError());
            m_spPlane->pos() = Vector2(100, 100);
            m_spPlane->vel() = Vector2(0.1, 0.1);
            m_spBackground->vel() = Vector2(0.0, 2.0f);
        }
        virtual ~GameState() {}

        virtual bool logic(unsigned int advance)
        {
            float t = advance*0.001f;

            if(Events::get().key(ALLEGRO_KEY_ESCAPE))
                return false;

            const float f = 100.0f;
            
            m_spPlane->vel() = Vector2();

            if(Events::get().key(ALLEGRO_KEY_UP))
                m_spPlane->vel().y = -f;
            if(Events::get().key(ALLEGRO_KEY_DOWN))
                m_spPlane->vel().y = f;
            if(Events::get().key(ALLEGRO_KEY_LEFT))
                m_spPlane->vel().x = -f;
            if(Events::get().key(ALLEGRO_KEY_RIGHT))
                m_spPlane->vel().x = f;

            m_spPlane->pos() += m_spPlane->vel() * t;
            m_spBackground->pos() += m_spBackground->vel();
            if(m_spBackground->pos().y > m_spBackground->h())
                m_spBackground->pos().y = 0.0;
            return true;
        }
        virtual void render() const
        {
            float old_y = m_spBackground->pos().y;

            m_spBackground->render();
            m_spBackground->pos().y -= m_spBackground->h();
            m_spBackground->render();
            m_spBackground->pos().y = old_y;

            m_spPlane->render();
        }
};

#endif

