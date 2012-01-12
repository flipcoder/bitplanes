#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>
#include <new>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include "System.h"
#include "IFallible.h"
#include "math/vector2.h"
#include "Image.h"
#include "IDepth.h"

class Sprite : public IDepth, public IFallible
{
    private:

        void nullify() {
            //m_pBitmap = nullptr;
        }

        Vector2 m_vPos;
        //Vector2 m_vVel;

    public:

        //Sprite(unsigned int width, unsigned int height) {
        //    nullify();
        //    m_pBitmap = al_create_bitmap(width, height);
        //    //al_convert_mask_to_alpha(m_pBitmap, al_map_rgb(255,0,255));
        //    if(!m_pBitmap)
        //        setError("Failed to create bitmap");
        //}
        Sprite() {
            //nullify();
            
            //al_convert_mask_to_alpha(m_pBitmap, al_map_rgb(255,0,255));
        }
        void destroy() {
            //al_destroy_bitmap(m_pBitmap);
            nullify();
        }
        virtual ~Sprite(){
            destroy();
        }
        //static Sprite* load(std::string fn) {
        //    Sprite* s = new (std::nothrow) Sprite(fn);
        //    if(s && s->hasError()) {
        //        delete s;
        //        s = nullptr;
        //    }
        //    return s;
        //}
        //static Sprite* loadAnimation(std::string fn, unsigned int width = 0, unsigned int height = 0) {
        //    return nullptr; //nyi
        //}
        //static Sprite* load(unsigned int width, unsigned int height) {
            //return new Sprite(width, height);
        //}
        void render() const {
            
        }
        void enqueue() const;
        float x() { return m_vPos.x; }
        float y() { return m_vPos.y; }
        //float w() { return m_pBitmap ? al_get_bitmap_width(m_pBitmap) : 0; }
        //float h() { return m_pBitmap ? al_get_bitmap_height(m_pBitmap) : 0; }

        Vector2& pos() {
            return m_vPos;
        }
        const Vector2& pos() const {
            return m_vPos;
        }
        //Vector2& vel() {
        //    return m_vVel;
        //}
        //const Vector2& vel() const {
        //    return m_vVel;
        //}
};

#endif

