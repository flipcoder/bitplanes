#include "System.h"
#include "GameState.h"

System :: System()
{
    nullify();
}

bool System :: init()
{
    if(allegro_init() != 0)
    {
        setError("Could not initialize Allegro");
        return false;
    }
    set_color_depth(32);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320*m_Scale, 240*m_Scale, 0, 0) != 0)
    {
        setError("Could not initialize graphics mode");
        return false;
    }
    if(install_keyboard() != 0)
    {
        setError("Could not initialize keyboard");
        return false;
    }

    m_pBuffer = create_bitmap(320, 240);
    if(!m_pBuffer)
    {
        setError("Unable to create buffer");
        return false;
    }
    clear_to_color(m_pBuffer, makecol(255,0,0));

    Freq::get(new Freq());
    pushState("game");
    
    return true;
}

System :: ~System()
{
    destroy_bitmap(m_pBuffer);
    allegro_exit();
}

bool System :: logic()
{
    bool ret = true;
    unsigned long now = Freq::get().getElapsedTime();
	unsigned long a = now - m_uiLastAdv;
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
    stretch_blit(m_pBuffer, screen,
        0, 0, SCREEN_W/m_Scale, SCREEN_H/m_Scale,
        0, 0, SCREEN_W, SCREEN_H);
}

bool System :: run()
{
    if(!init())
        return false;

    while(pollState())
    {
        if(keyboard_needs_poll())
            poll_keyboard();
        if(key[KEY_ESC]) {
            key[KEY_ESC] = 0;
            popState();
        }

        logic();
        render();
    }

    return true;
}

IRealtime* System :: newState(const std::string id)
{
    IRealtime* state = nullptr;
    if(id == "game")
        state = new GameState();
    return state;
}

