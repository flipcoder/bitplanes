#include "Events.h"
#include "System.h"

Events :: Events()
{
    nullify();
    m_pQueue = al_create_event_queue();
    if(m_pQueue)
    {
        al_register_event_source(m_pQueue, al_get_keyboard_event_source());
        al_register_event_source(m_pQueue, al_get_mouse_event_source());
        al_register_event_source(m_pQueue, al_get_display_event_source(System::get().display()));
    }
}

Events :: ~Events() {}
