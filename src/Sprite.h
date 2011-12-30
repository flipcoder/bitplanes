#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include "System.h"
#include "IFallible.h"
#include "math/vector2.h"

class Sprite : public IFallible
{
    private:

        ALLEGRO_BITMAP* m_pBitmap;

        void nullify() {
            m_pBitmap = nullptr;
        }

        Vector2 m_vPos;
        Vector2 m_vVel;

    public:

        Sprite(unsigned int width, unsigned int height) {
            nullify();
            m_pBitmap = al_create_bitmap(width, height);
            if(!m_pBitmap)
                setError("Failed to create bitmap");
        }
        Sprite(std::string fn) {
            nullify();
            m_pBitmap = al_load_bitmap(fn.c_str());
        }
        void destroy() {
            al_destroy_bitmap(m_pBitmap);
            nullify();
        }
        virtual ~Sprite(){
            destroy();
        }
        static Sprite* load(std::string fn) {
            return new Sprite(fn);
        }
        static Sprite* loadAnimation(std::string fn, unsigned int width = 0, unsigned int height = 0) {
            return nullptr; //nyi
        }
        static Sprite* load(unsigned int width, unsigned int height) {
            return new Sprite(width, height);
        }
        void render();
        float x() { return m_vPos.x; }
        float y() { return m_vPos.y; }
        unsigned int w() { return m_pBitmap ? al_get_bitmap_width(m_pBitmap) : 0; }
        unsigned int h() { return m_pBitmap ? al_get_bitmap_height(m_pBitmap) : 0; }

        Vector2& pos() {
            return m_vPos;
        }
        const Vector2& pos() const {
            return m_vPos;
        }
        Vector2& vel() {
            return m_vVel;
        }
        const Vector2& vel() const {
            return m_vVel;
        }
};

#endif

