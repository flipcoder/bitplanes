#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_acodec.h>
#include "IFallible.h"
#include "IStaticInstance.h"
#include "IStateManager.h"
#include "IState.h"
#include "Freq.h"
#include "Sprite.h"
#include "Events.h"

class System : public IStaticInstance<System>, public IFallible, public IStateManager<std::string, IState>
{
    private:

        bool m_bQuit;
        unsigned long m_uiLastAdv;
        ALLEGRO_BITMAP* m_pBuffer;
        ALLEGRO_DISPLAY* m_pDisplay;
        unsigned int m_Scale;

        void nullify(){
            m_bQuit = false;
            m_uiLastAdv = 0;
            m_Scale = 2;
            m_pBuffer = nullptr;
            m_pDisplay = nullptr;
        }


    public:

        System();
        virtual ~System();

        bool run();
        bool logic();
        void render() const;

        // State manager acts as own factory

        bool quitFlag() const { return m_bQuit; }
        void quit(bool b = true) { m_bQuit = b; }

        virtual IState* newState(const std::string id);
        
        ALLEGRO_BITMAP* buffer() { return m_pBuffer; }
        ALLEGRO_DISPLAY* display() { return m_pDisplay; }

        const float w() const { return m_pDisplay ? al_get_display_width(m_pDisplay) : 0.0f; }
        const float h() const { return m_pDisplay ? al_get_display_height(m_pDisplay) : 0.0f; }
};

#endif

