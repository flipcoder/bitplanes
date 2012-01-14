#ifndef _EVENTS_H
#define _EVENTS_H

#include <allegro5/allegro5.h>
#include "IStaticInstance.h"
#include "IRealtime.h"
#include "math/vector2.h"

class Events : public IStaticInstance<Events>, public IRealtime
{
    public:

        static const int MAX_KEYS = 512;

    private:
        
        bool m_bKey[ALLEGRO_KEY_MAX];
        ALLEGRO_EVENT_QUEUE* m_pQueue;
        Vector2 m_vMouse;

        void nullify() {
            for(int i=0; i<ALLEGRO_KEY_MAX; i++)
                m_bKey[i] = false;
            m_pQueue = nullptr;
        }

    public:

        Events(ALLEGRO_DISPLAY* display);
        virtual ~Events();

        virtual bool logic(unsigned int advance);
        bool key(unsigned int idx) const {
            return m_bKey[idx];
        }
        bool keyd(unsigned int idx) {
            bool b = m_bKey[idx];
            m_bKey[idx] = false;
            return b;
        }
        Vector2 mousePos() const { return m_vMouse; }
};

#endif

