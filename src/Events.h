#ifndef _EVENTS_H
#define _EVENTS_H

#include <allegro5/allegro5.h>
#include "IStaticInstance.h"
#include "IRealtime.h"
#include "math/vector2.h"

// TODO: Add "Controller" system that can check certain keys based on bindings

class Events : public IStaticInstance<Events>, public IRealtime
{
    public:

        static const unsigned int MAX_KEYS = 512;
        static const unsigned int MAX_MOUSE_BUTTONS = 8;

    private:
        
        bool m_bMouse[MAX_MOUSE_BUTTONS];
        bool m_bKey[ALLEGRO_KEY_MAX];
        ALLEGRO_EVENT_QUEUE* m_pQueue;
        Vector2 m_vMouse;

        void nullify() {
            for(int i=0; i<ALLEGRO_KEY_MAX; i++)
                m_bKey[i] = false;
            for(int i=0; i<MAX_MOUSE_BUTTONS; i++)
                m_bMouse[i] = false;
            m_pQueue = nullptr;
        }

    public:

        Events(ALLEGRO_DISPLAY* display);
        virtual ~Events();

        virtual void logic(float t);
        bool key(unsigned int idx) const {
            return m_bKey[idx];
        }
        bool keyd(unsigned int idx) {
            bool b = m_bKey[idx];
            m_bKey[idx] = false;
            return b;
        }
        Vector2 mousePos() const { return m_vMouse; }
        bool mouse(unsigned int idx) const {
            return m_bMouse[idx];
        }
        bool moused(unsigned int idx) {
            bool b = m_bMouse[idx];
            m_bMouse[idx] = false;
            return b;
        }
};

#endif

