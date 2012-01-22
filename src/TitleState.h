#ifndef _TITLE_STATE_H
#define _TITLE_STATE_H

#include "Player.h"
#include "Terrain.h"
#include "World.h"
#include "Text.h"

class TitleState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        std::shared_ptr<Font> m_spFont;
        std::shared_ptr<Text> m_spText;

        void nullify() {}

    public:
        TitleState() {
            nullify();

            m_spWorld.reset(new World());
            m_spWorld->vel(Vector2(0.0f, -100.0f));// in future: set by world script

            std::shared_ptr<Object> terrain(new Terrain("data/gfx/terrain/forest.png"));
            std::shared_ptr<Object> logo(new Object("data/gfx/interface/logo.png"));
            logo->pos().x += (System::get().size().x - logo->size().x)/2.0f; // center logo
            logo->pos().y += System::get().size().y / 4.0f;

            m_spFont.reset(new Font("data/fonts/visitor2.ttf", 32.0f));
            m_spText.reset(new Text(m_spFont,
                "PRESS START",
                Vector2(
                    System::get().size().x/2.0f,
                    (2.0f*System::get().size().y)/4.0
                ),
                Color(), Font::CENTER
            ));

            m_spWorld->add(terrain);
            m_spWorld->add(logo);
        }
        virtual ~TitleState() {}

        virtual bool logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10))
                return false;
            if(Events::get().moused(0))
                System::get().swapState("game");
            
            m_spWorld->logic(t);
            return true;
        }
        virtual void render() const
        {
            m_spWorld->render();
            m_spText->render();
        }
};

#endif

