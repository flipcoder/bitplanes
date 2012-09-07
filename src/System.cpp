#include "System.h"
#include "GameState.h"
#include "TitleState.h"
#include "Log.h"
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Util.h"
#include "Audio.h"
#include "Filesystem.h"

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
    
    Audio::get(new Audio());
    // TEMP: hardcoded values
    Audio::get().listener()->scale(320.0f);
    Audio::get().listener()->pos(160.0f, 0.0f);

    if(!al_install_keyboard())
        throw Failure("Could not initialize keyboard");
    if(!al_install_mouse())
        throw Failure("Could not initialize mouse");
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

    //m_ImageResources.addExtension("png");
    m_ImageResources.addPath("data/objects/");
    m_ImageResources.addPath("data/backdrops/");
    
    m_spSession.reset(new Session());

    dtor.resolve();
    // Note: Do not load any sprites, images, or anything that may access System::get() while in this constructor
}

System :: ~System()
{
    destroyStateManager();
    al_set_target_bitmap(nullptr);
    if(m_pDisplay)
        al_destroy_display(m_pDisplay);
}

bool System :: logic()
{
    Freq::Time t;
    while(!(t = Freq::get().tick()).milliseconds()) {}

    Events::get().logic(t.seconds());
    Audio::get().logic(t.seconds());
    IState* state = currentState();
    if(state)
        state->logic(t.seconds());

    return true;
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

        if(quitFlag())
            destroyStateManager();
    }

    return true;
}

IState* System :: newState(const std::string id)
{
    IState* state = nullptr;
    
    try{
        if(id == "game")
            state = new GameState();
        else if(id == "title")
            state = new TitleState();
        if(state->hasError()){
            delete state;
            state = NULL;
        }
    }catch(const Failure&){}

    return state;
}

void System :: depthEnqueue(const std::shared_ptr<const IDepthSortable>& s)
{
    assert(m_bQueued);
    m_DepthQueue.enqueue(s);
}

