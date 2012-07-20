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
        int m_Size;

        void nullify() {
            m_pFont = nullptr;
            m_Size = 0;
        }
    public:
        Font(const std::string& fn, int size){
            nullify();
            scoped_dtor<Font> dtor(this);

            m_Size = size;
            m_pFont = al_load_ttf_font(fn.c_str(), size, 0);
            if(!m_pFont)
                throw Failure("Failed to load font");

            dtor.resolve();
        }
        virtual ~Font() {
            al_destroy_font(m_pFont);
        }

        int size() const { return m_Size; }
        ALLEGRO_FONT* allegro() const { return m_pFont; }
};

#endif

