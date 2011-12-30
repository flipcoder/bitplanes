#ifndef _EVENTS_H
#define _EVENTS_H

#include <allegro5/allegro5.h>
#include "IStaticInstance.h"
#include "IRealtime.h"

class Events : public IStaticInstance<Events>, public IRealtime
{
    public:

        static const int MAX_KEYS = 512;

    private:
        
        bool m_bKey[ALLEGRO_KEY_MAX];
        ALLEGRO_EVENT_QUEUE* m_pQueue;

        void nullify() {
            for(int i=0; i<ALLEGRO_KEY_MAX; i++)
                m_bKey[i] = false;
            m_pQueue = nullptr;
        }

    public:

        Events();
        virtual ~Events();

        virtual bool logic(unsigned int advance) {
            ALLEGRO_EVENT event;
            while(al_get_next_event(m_pQueue, &event))
            {
                switch(event.type)
                {
                    case ALLEGRO_EVENT_DISPLAY_CLOSE:
                        return false;
                }
            }
            return true;
        }

        bool key(unsigned int idx) const {
            return m_bKey[idx];
        }
        bool keyd(unsigned int idx) {
            bool b = m_bKey[idx];
            m_bKey[idx] = false;
            return b;
        }
};

#endif

