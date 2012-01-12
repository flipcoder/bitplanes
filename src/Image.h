#ifndef _IMAGE_H
#define _IMAGE_H

#include <allegro5/allegro5.h>
#include "math/vector2.h"
#include "IRenderable.h"
#include "IFallible.h"

// OO wrapper for allegro bitmap
class Image : public IRenderable, public IFallible
{
    private:

        ALLEGRO_BITMAP* m_pBitmap;

        void nullify() {
            m_pBitmap = nullptr;
        }

    public:
        
        Image(const std::string& fn);
        Image(int w, int h);
        void render(const Vector2& pos);
        void render(const Vector2& pos, const Vector2& size);
        ALLEGRO_BITMAP* bitmap() { return m_pBitmap; }
        const ALLEGRO_BITMAP* bitmap() const { return m_pBitmap; }
        virtual ~Image();
};

#endif

