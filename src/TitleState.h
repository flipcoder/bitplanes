#ifndef _TITLE_STATE_H
#define _TITLE_STATE_H

#include "Player.h"
#include "Backdrop.h"
#include "World.h"
#include "Text.h"
#include "Audio.h"

class TitleState : public IState
{
    private:

        std::shared_ptr<World> m_spWorld;
        std::shared_ptr<Font> m_spFont;
        std::shared_ptr<Text> m_spText;
        std::shared_ptr<Object> m_spLogo;
        std::shared_ptr<Audio::Stream> m_spMusic;

        Freq::Timed<Vector2> m_TitleDrop;
        Freq::Timed<Vector2> m_TextRise;
        boost::optional<Freq::Timed<float>> m_TextFade;

        void nullify() {}

    public:
        TitleState() {
            nullify();

            m_spWorld.reset(new World());
            std::shared_ptr<Object> backdrop(new Backdrop("forest.ini"));
            backdrop->vel(0.0f, 200.0f);

            m_spLogo.reset(new Object("data/interface/logo.png"));

            m_TitleDrop = Freq::Timed<Vector2>(
                Freq::Time::seconds(1.0f),
                Vector2((System::get().size().x - m_spLogo->size().x)/2.0f, -m_spLogo->size().y),
                Vector2((System::get().size().x - m_spLogo->size().x)/2.0f, System::get().size().y / 4.0f)
            );

            m_spFont.reset(new Font("data/fonts/visitor2.ttf", 32.0f));
            m_spText.reset(new Text(m_spFont,
                "PRESS START",
                Vector2(),
                Color(),
                Font::CENTER
            ));

            //m_TextFade.set(Freq::Time(100),0.0f,1.0f);

            m_TextRise = Freq::Timed<Vector2>(
                Freq::Time::seconds(1.0f),
                Vector2(System::get().size().x/2.0f, System::get().size().y + m_spFont->size()),
                Vector2(System::get().size().x/2.0f, System::get().size().y / 2.0f)
            );

            try{
                m_spMusic.reset(new Audio::Stream("data/audio/lobby.ogg"));
                if(m_spMusic)
                    m_spMusic->play(Audio::Stream::REPEAT);
            } catch(Failure& f) {
                //Log::get().write("Could not load music.");
            }
            
            m_spWorld->add(backdrop);
            m_spWorld->add(m_spLogo);
        }
        virtual ~TitleState() {}

        virtual void logic(float t)
        {
            if(Events::get().key(ALLEGRO_KEY_F10)) {
                System::get().quit();
                return;
            }

            m_spLogo->pos(m_TitleDrop.get());
            m_spText->pos(m_TextRise.get());

            if(m_TitleDrop.hasElapsed() && !m_TextFade)
                m_TextFade = Freq::Timed<float>(Freq::Time(100),0.0f,1.0f);
            
            if(m_TextFade)
            {
                if(Events::get().moused(0))
                    System::get().swapState("game");

                if(m_TextFade->hasElapsed()) {
                    Color c = m_spText->color();
                    float f = m_TextFade->get();
                    c.set(f,f);
                    m_spText->color(c);
                    m_TextFade->reverse();
                }
            }

            m_spWorld->logic(t);
        }
        virtual void render() const
        {
            m_spWorld->render();
            m_spText->render();
        }
};

#endif

