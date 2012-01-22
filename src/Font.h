#ifndef _FONT_H
#define _FONT_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "IFallible.h"

class Font : public IFallible
{
    public:

        enum Align
        {
            LEFT = -1,
            CENTER = 0,
            RIGHT = 1
        };

    private:
        ALLEGRO_FONT* m_pFont;

        void nullify() {
            m_pFont = nullptr;
        }
    public:
        Font(const std::string& fn, int size) {
            nullify();
            m_pFont = al_load_ttf_font(fn.c_str(), size, 0);
            if(!m_pFont){
                setError("Failed to load font");
                throw Failure();
            }
        }
        virtual ~Font() {
            al_destroy_font(m_pFont);
        }

        ALLEGRO_FONT* allegro() const { return m_pFont; }
};

#endif

