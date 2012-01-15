#include "System.h"
#include "Sprite.h"

Sprite :: Sprite(const std::string& fn)
{
    nullify();
    setImage(System::get().imageResources().ensure_shared(fn));
}


void Sprite :: render() const
{
    std::shared_ptr<const Image> image;
    if(!(image = m_wpImage.lock()))
        return;

    // TODO: Probably move this queue crap out of system and into a Renderer class
    if(System::get().queued()) {
        std::shared_ptr<const IDepth> spthis = shared_from_this();
        System::get().depthEnqueue(spthis);
    } else {
        if(m_vScale == Vector2(1.0f, 1.0f))
            al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(image->bitmap()), m_vPos.x, m_vPos.y, 0);
        else
            al_draw_scaled_bitmap(const_cast<ALLEGRO_BITMAP*>(image->bitmap()),
                0.0f, 0.0f,
                al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(image->bitmap())),
                al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(image->bitmap())),
                m_vPos.x, m_vPos.y,
                al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(image->bitmap())) * m_vScale.x,
                al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(image->bitmap())) * m_vScale.y,
                0);
    }
}

