#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <allegro.h>
#include "IFallible.h"
#include "IStaticInstance.h"
#include "IStateManager.h"
#include "IRealtime.h"
#include "Freq.h"
#include "Sprite.h"

class System : public IStaticInstance<System>, public IFallible, public IStateManager<std::string, IRealtime>
{
    private:

        bool m_bQuit;
        unsigned long m_uiLastAdv;
        BITMAP* m_pBuffer;
        unsigned int m_Scale;

        void nullify(){
            m_bQuit = false;
            m_uiLastAdv = 0;
            m_Scale = 4;
        }

    public:

        System();
        virtual ~System();

        bool init();
        bool run();
        bool logic();
        void render() const;

        // State manager acts as own factory

        bool quitFlag() const { return m_bQuit; }
        void quit(bool b = true) { m_bQuit = b; }

        virtual IRealtime* newState(const std::string id);
        
        BITMAP* buffer() { return m_pBuffer; }
};

#endif

