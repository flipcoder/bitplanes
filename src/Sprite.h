#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include "System.h"
#include "IFallible.h"

class Sprite : public IFallible
{
    private:

        ALLEGRO_BITMAP* m_pBitmap;
        float m_fX,m_fY;

        void nullify() {
            m_pBitmap = nullptr;
            m_fX = m_fY = 0.0f;
        }

    public:

        Sprite(unsigned int width, unsigned int height) {
            nullify();
            m_pBitmap = al_create_bitmap(width, height);
            if(!m_pBitmap)
                setError("Failed to create bitmap");
        }
        Sprite(std::string fn) {
            nullify();
            //m_pBitmap = load_bitmap(fn.c_str(), pal);
        }
        void destroy() {
            al_destroy_bitmap(m_pBitmap);
            nullify();
        }
        virtual ~Sprite(){
            destroy();
        }
        static std::shared_ptr<Sprite>&& load(std::string fn) {
            return std::move(std::shared_ptr<Sprite>(new Sprite(fn)));
        }
        static std::shared_ptr<Sprite>&& load(unsigned int width, unsigned int height) {
            return std::move(std::shared_ptr<Sprite>(new Sprite(width,height)));
        }
        void render();
        float x() { return m_fX; }
        float y() { return m_fY; }
        unsigned int w() { return m_pBitmap ? al_get_bitmap_width(m_pBitmap) : 0; }
        unsigned int h() { return m_pBitmap ? al_get_bitmap_height(m_pBitmap) : 0; }
};

#endif

