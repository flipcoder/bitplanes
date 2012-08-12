#include "System.h"
#include "GameState.h"
#include "TitleState.h"
#include "Log.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include "Util.h"

System :: System()
{
    nullify();
    scoped_dtor<System> dtor(this);

    Log::get(new Log());

    if(!al_init())
        throw Failure("Could not initialize Allegro");
    //al_set_color_depth(32);
    //if(al_set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320*m_Scale, 240*m_Scale, 0, 0) != 0)
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    //al_set_new_display_option(ALLEGRO_VSYNC, 2, ALLEGRO_REQUIRE);
    if(!(m_pDisplay = al_create_display(320*m_Scale, 480*m_Scale)))
        throw Failure("Could not initialize graphics mode");
    al_set_window_title(m_pDisplay, "bitplanes");
    if(!al_init_image_addon())
        throw Failure("Could not initialize image addon");
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();
    if(!al_install_keyboard())
        throw Failure("Could not initialize keyboard");
    if(!al_install_mouse())
        throw Failure("Could not initialize keyboard");
    al_hide_mouse_cursor(m_pDisplay);

    m_spBuffer.reset(new Image(320, 480));
    if(!m_spBuffer)
       throw Failure("Unable to create buffer");
    
    Events::get(new Events(m_pDisplay));
    Freq::get(new Freq());
    //m_uiLastAdv = Freq::get().getElapsedTime();

    // clear buffer
    al_set_target_bitmap(m_spBuffer->bitmap());
    //al_set_target_backbuffer(m_pDisplay);
    al_clear_to_color(al_map_rgb(0,0,0));
    // push default mode
    pushState("title");

    dtor.resolve();
}

System :: ~System()
{
    destroyStateManager();
    al_set_target_bitmap(nullptr);
    al_destroy_display(m_pDisplay);
}

bool System :: logic()
{
    bool ret = true;
    unsigned long now, adv;
    do{
        now = Freq::get().getElapsedTime();
        if(m_uiLastAdv == 0)
            m_uiLastAdv = now;
        adv = (now - m_uiLastAdv);
        if(adv > 1) // if <1000tick/s stop waiting
            break;
        al_rest(0.001f);
    }while(true);

    m_uiLastAdv = now;

    float t = adv * 0.001f;

    if(!Events::get().logic(t))
        return false;
    IState* state = currentState();
    if(state)
    {
        if(!state->logic(t))
            ret = false;
    }
    else
        return false;

    return ret;
}

void System :: render()
{
    const IState* state = currentState();

    queue();
    if(state)
        state->render();

    queue(false);
    al_set_target_bitmap(m_spBuffer->bitmap());
    al_clear_to_color(al_map_rgb(0,0,0));
    m_DepthQueue.render(); // not const

    if(m_pDisplay && m_spBuffer)
    {
        al_set_target_backbuffer(m_pDisplay);
        //al_clear_to_color(al_map_rgb(0,0,0));
        //al_draw_bitmap(m_spBuffer->bitmap(), 0,0,0);
        al_draw_scaled_bitmap(m_spBuffer->bitmap(),
            0, 0,
            al_get_bitmap_width(m_spBuffer->bitmap()),
            al_get_bitmap_height(m_spBuffer->bitmap()),
            0, 0,
            al_get_display_width(m_pDisplay), 
            al_get_display_height(m_pDisplay),
            0);
        al_flip_display();
    }
}

bool System :: run()
{
    while(pollState())
    {
        if(!logic())
            break;
        render();
    }

    return true;
}

IState* System :: newState(const std::string id)
{
    IState* state = nullptr;
    if(id == "game")
        state = new GameState();
    else if(id == "title")
        state = new TitleState();
    if(state->hasError()){
        delete state;
        state = NULL;
    }
    return state;
}

void System :: depthEnqueue(const std::shared_ptr<const IDepthSortable>& s)
{
    assert(m_bQueued);
    m_DepthQueue.enqueue(s);
}

