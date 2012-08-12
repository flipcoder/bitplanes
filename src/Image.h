#ifndef _IMAGE_H
#define _IMAGE_H

#include <allegro5/allegro5.h>
#include "math/vector2.h"
#include "IFallible.h"
#include "Graphics.h"

// OO wrapper for allegro bitmap
class Image : public IFallible
{
    private:

        ALLEGRO_BITMAP* m_pBitmap;

        void nullify() {
            m_pBitmap = nullptr;
        }

    public:
        
        Image(const std::string& fn);
        Image(int w, int h);
        virtual ~Image();

        void render(const Vector2& pos) const;
        //void render(const Vector2& pos, const Vector2& size);
        ALLEGRO_BITMAP* bitmap() { return m_pBitmap; }
        const ALLEGRO_BITMAP* bitmap() const { return m_pBitmap; }
        Vector2 size() const {
            if(!m_pBitmap)
                return Vector2();
            return Vector2(al_get_bitmap_width(m_pBitmap), al_get_bitmap_height(m_pBitmap));
        }

        Color pixel(int x, int y) const {
            Color c;
            c.allegro(al_get_pixel(const_cast<ALLEGRO_BITMAP*>(m_pBitmap),x,y));
            return c;
        }
};

#endif

