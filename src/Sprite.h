#ifndef _SPRITE_H
#define _SPRITE_H

#include <string>
#include <memory>
#include <new>
#include <bitset>
#include <tuple>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <boost/optional/optional.hpp>
#include "Util.h"
#include "System.h"
#include "IFallible.h"
#include "math/vector2.h"
#include "Image.h"
#include "IDepthSortable.h"
#include "Graphics.h"
#include "IMovable.h"

class Sprite : public IDepthSortable, public IFallible, public IMovable
{
    public:
        enum eFlags {
            F_TILE,
            MAX_FLAGS
        };

    private:

        void nullify() {
            m_vScale = Vector2(1.0f, 1.0f);
        }

        Vector2 m_vScale;
        //Vector2 m_vVel;
        
        std::bitset<MAX_FLAGS> m_bsFlags;
        std::shared_ptr<const Image> m_spImage;
        boost::optional<Color> m_Tint;

        boost::optional<std::tuple<int,int,int>> m_Blend;

    public:

        
        //Sprite(unsigned int width, unsigned int height) {
        //    nullify();
        //    m_pBitmap = al_create_bitmap(width, height);
        //    //al_convert_mask_to_alpha(m_pBitmap, al_map_rgb(255,0,255));
        //    if(!m_pBitmap)
        //        setError("Failed to create bitmap");
        //}
        Sprite() {
            nullify();
            //scoped_dtor dtor(this);
            
            // adding anything here? put back the dtor callbacks

            //dtor.resolve();
        }
        Sprite(const std::string& fn);
        Sprite(const std::shared_ptr<const Image>& image) {
            nullify();
            scoped_dtor<Sprite> dtor(this);
            setImage(image);
            dtor.resolve();
        }
        void destroy() {
            nullify();
        }
        virtual ~Sprite(){
            destroy();
        }

        void setImage(const std::shared_ptr<const Image>& image) {
            m_spImage = image;
        }
        void erase() {
            m_spImage.reset();
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
        void render() const;

        //float w() { return m_pBitmap ? al_get_bitmap_width(m_pBitmap) : 0; }
        //float h() { return m_pBitmap ? al_get_bitmap_height(m_pBitmap) : 0; }
        std::bitset<MAX_FLAGS>& flags() { return m_bsFlags; }
        const std::bitset<MAX_FLAGS>& flags() const { return m_bsFlags; }
        
        Vector2 size() const {
            return m_spImage->size();
        }
        Vector2& scale() {
            return m_vScale;
        }
        const Vector2& scale() const {
            return m_vScale;
        }
        //Vector2& vel() {
        //    return m_vVel;
        //}
        //const Vector2& vel() const {
        //    return m_vVel;
        //}
        const std::shared_ptr<const Image>& image() const { return m_spImage; }
        std::shared_ptr<const Image>& image() { return m_spImage; }
        
        void tint(Color c) {
            m_Tint = c;
        }
        boost::optional<Color> tint() const { return m_Tint; }
        void untint() {
            m_Tint = boost::optional<Color>();
        }

        void blend(int op, int src, int dest) {
            m_Blend = std::tuple<int,int,int>(op,src,dest);
        }
        void unblend() {
            m_Blend = boost::optional<std::tuple<int,int,int>>();
        }
        boost::optional<std::tuple<int,int,int>> blend() const { return m_Blend; };
};

#endif

