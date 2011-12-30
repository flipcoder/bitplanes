#ifndef _GAME_STATE_H
#define _GAME_STATE_H

class GameState : public IRealtime
{
    private:

        void nullify() {}

        std::shared_ptr<Sprite> m_pBackground;
        std::shared_ptr<Sprite> m_pPlane;

    public:
        GameState() {
            m_pBackground.reset(Sprite::load("data/gfx/backgrounds/forest.png"));
            if(!m_pBackground.get() || m_pBackground.get()->hasError())
                setError(m_pBackground.get()->moveError());
        }
        virtual ~GameState() {}

        virtual bool logic(unsigned int advance)
        {
            return true;
        }
        virtual void render() const
        {
            m_pBackground.get()->render();
        }
};

#endif

