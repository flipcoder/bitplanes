#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <boost/optional.hpp>
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
#include "ResourceCache.h"
#include "Session.h"

class System :
    public IStaticInstance<System>,
    public IFallible,
    public IStateManager<std::string, IState>
{
    private:

        bool m_bQuit;
        bool m_bQueued;
        unsigned long m_uiLastAdv;
        std::shared_ptr<Image> m_spBuffer;
        ALLEGRO_DISPLAY* m_pDisplay;
        unsigned int m_Scale;
        DepthQueue m_DepthQueue;
        ResourceCache<Image> m_ImageResources;
        std::shared_ptr<Session> m_spSession;
        boost::optional<Freq::Alarm> m_ScreenFade;

        //std::list<Alarm*> m_AlarmList;

        void nullify(){
            m_bQuit = false;
            m_bQueued = false;
            m_uiLastAdv = 0;
            m_Scale = 2;
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

        Vector2 size() const { return m_spBuffer ? m_spBuffer->size() : Vector2(); }
        float w() const { return m_spBuffer ? m_spBuffer->size().x : 0.0f; }
        float h() const { return m_spBuffer ? m_spBuffer->size().y : 0.0f; }

        void depthEnqueue(const std::shared_ptr<const IDepthSortable>& s);
        bool queued() const { return m_bQueued; }
        void queue(bool b = true) { m_bQueued = b; }

        ResourceCache<Image>& imageResources() { return m_ImageResources; }
        const ResourceCache<Image>& imageResources() const { return m_ImageResources; }
        
        Session* session() { return m_spSession.get(); }
        const Session* session() const { return m_spSession.get(); }
        Session* newSession() {
            m_spSession.reset(new Session());
            return m_spSession.get();
        }

        float scale() const { return 1.0f*m_Scale; }

        // TODO: Add timed screen fader (use Freq::Timed) (maybe with retro stairstep interp function?)
        //  Use m_ScreenFade (above)
};

#endif

