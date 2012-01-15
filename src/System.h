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
#include "Image.h"
#include "DepthQueue.h"
#include "Image.h"
#include "ResourceMap.h"

class System : public IStaticInstance<System>, public IFallible, public IStateManager<std::string, IState>
{
    private:

        bool m_bQuit;
        bool m_bQueued;
        unsigned long m_uiLastAdv;
        std::shared_ptr<Image> m_spBuffer;
        ALLEGRO_DISPLAY* m_pDisplay;
        unsigned int m_Scale;
        DepthQueue m_DepthQueue;
        ResourceMap<Image> m_ImageResources;

        void nullify(){
            m_bQuit = false;
            m_bQueued = false;
            m_uiLastAdv = 0;
            m_Scale = 3;
            m_pDisplay = nullptr;
        }


    public:

        System();
        virtual ~System();

        bool run();
        bool logic();
        void render();

        // State manager acts as own factory

        bool quitFlag() const { return m_bQuit; }
        void quit(bool b = true) { m_bQuit = b; }

        virtual IState* newState(const std::string id);
        
        ALLEGRO_BITMAP* buffer() { return m_spBuffer->bitmap(); }
        ALLEGRO_DISPLAY* display() { return m_pDisplay; }

        const float w() const { return m_pDisplay ? al_get_display_width(m_pDisplay) : 0.0f; }
        const float h() const { return m_pDisplay ? al_get_display_height(m_pDisplay) : 0.0f; }

        void depthEnqueue(const std::shared_ptr<const IDepth>& s);
        bool queued() const { return m_bQueued; }
        void queue(bool b = true) { m_bQueued = b; }

        ResourceMap<Image>& imageResources() { return m_ImageResources; }
        const ResourceMap<Image>& imageResources() const { return m_ImageResources; }

        float scale() const { return 1.0f*m_Scale; }
};

#endif

