#ifndef _IMAGE_H
#define _IMAGE_H

#include <allegro5/allegro5.h>
#include "System.h"

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
        void render(const Vector2& pos);
        void render(const Vector2& pos, const Vector2& size);
        virtual ~Image();
};

#endif

