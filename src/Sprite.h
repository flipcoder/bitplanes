#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>
#include <allegro.h>
#include "System.h"
#include "IFallible.h"

class Sprite : public IFallible
{
    private:

        BITMAP* m_pBitmap;
        float m_fX,m_fY;

    public:

        Sprite(unsigned int width, unsigned int height) {
            m_fX = m_fY = 0.0f;
            m_pBitmap = create_bitmap(width, height);
        }
        Sprite(std::string fn) {
            m_fX = m_fY = 0.0f;
            PALETTE pal;
            m_pBitmap = load_bitmap(fn.c_str(), pal);
        }
        virtual ~Sprite(){
            destroy_bitmap(m_pBitmap);
        }
        static std::unique_ptr<Sprite>&& load(std::string fn) {
            return std::unique_ptr<Sprite>(new Sprite(fn));
        }
        static std::unique_ptr<Sprite>&& load(unsigned int width, unsigned int height) {
            return std::unique_ptr<Sprite>(new Sprite(width,height));
        }
        void render();
        float x() { return m_fX; }
        float y() { return m_fY; }
        unsigned int w() { return m_pBitmap ? m_pBitmap->w : 0; }
        unsigned int h() { return m_pBitmap ? m_pBitmap->h : 0; }
};

#endif

