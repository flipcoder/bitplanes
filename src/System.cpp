#include "System.h"
#include "GameState.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>

System :: System()
{
    nullify();
}

bool System :: init()
{
    destroy();

    if(!al_init())
    {
        setError("Could not initialize Allegro");
        return false;
    }
    //al_set_color_depth(32);
    //if(al_set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320*m_Scale, 240*m_Scale, 0, 0) != 0)
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    if(!(m_pDisplay = al_create_display(320*m_Scale, 240*m_Scale)))
    {
        setError("Could not initialize graphics mode");
        return false;
    }
    al_init_font_addon();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    if(!al_install_keyboard())
    {
        setError("Could not initialize keyboard");
        return false;
    }

    m_pBuffer = al_create_bitmap(320, 240);
    if(!m_pBuffer)
    {
        setError("Unable to create buffer");
        return false;
    }
    
    Events::get(new Events());
    Freq::get(new Freq());

    // clear buffer
    al_set_target_bitmap(m_pBuffer);
    al_clear_to_color(al_map_rgb(0,0,0));


    // push default mode
    pushState("game");
    return true;
}

System :: ~System()
{
    destroy();
}

void System :: destroy()
{
    al_destroy_bitmap(m_pBuffer);
    al_destroy_display(m_pDisplay);
}

bool System :: logic()
{
    bool ret = true;
    unsigned long now = Freq::get().getElapsedTime();
	unsigned long a = now - m_uiLastAdv;
    if(!Events::get().logic(a))
        return false;
    IRealtime* state = currentState();
    if(state)
        if(!state->logic(a))
            ret = false;
    m_uiLastAdv = now;
    return ret;
}

void System :: render() const
{
    const IRealtime* state = currentState();
    if(state)
        state->render();

    al_set_target_backbuffer(m_pDisplay);
    al_draw_scaled_bitmap(m_pBuffer,
        0, 0,
        al_get_bitmap_width(m_pBuffer),
        al_get_bitmap_height(m_pBuffer),
        0, 0,
        al_get_display_width(m_pDisplay), 
        al_get_display_height(m_pDisplay),
        0);
    al_flip_display();
    al_clear_to_color(al_map_rgb(0,0,0));
    al_set_target_bitmap(m_pBuffer);
}

bool System :: run()
{
    if(!init())
        return false;

    while(pollState())
    {
        if(!logic())
            break;
        render();
    }

    return true;
}

IRealtime* System :: newState(const std::string id)
{
    IRealtime* state = nullptr;
    if(id == "game")
        state = new GameState();
    if(state->hasError()){
        delete state;
        state = NULL;
    }
    return state;
}

