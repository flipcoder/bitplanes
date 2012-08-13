#include "Events.h"
#include "System.h"

Events :: Events(ALLEGRO_DISPLAY* display)
{
    nullify();
    m_pQueue = al_create_event_queue();
    // past this point, nothing should throw (use scoped_dtor if this isn't the case)
    if(m_pQueue)
    {
        al_register_event_source(m_pQueue, al_get_keyboard_event_source());
        al_register_event_source(m_pQueue, al_get_mouse_event_source());
        al_register_event_source(m_pQueue, al_get_display_event_source(display));
    }
}

bool Events :: logic(float advance)
{
    ALLEGRO_EVENT event;
    while(al_get_next_event(m_pQueue, &event))
    {
        switch(event.type)
        {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                return false;

            case ALLEGRO_EVENT_KEY_DOWN:
                m_bKey[event.keyboard.keycode] = true;
                break;
                
            case ALLEGRO_EVENT_KEY_UP:
                m_bKey[event.keyboard.keycode] = false;
                break;

            case ALLEGRO_EVENT_MOUSE_AXES:
            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                m_vMouse = Vector2(event.mouse.x, event.mouse.y);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                m_bMouse[event.mouse.button-1] = true;
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                m_bMouse[event.mouse.button-1] = false;
                break;
        }
    }
    return true;
}

Events :: ~Events()
{
    al_destroy_event_queue(m_pQueue);
}

