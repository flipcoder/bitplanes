#include "System.h"
#include "Sprite.h"
#include <cmath>

Sprite :: Sprite(const std::string& fn)
{
    nullify();
    setImage(System::get().imageResources().ensure_shared(fn));
}


void Sprite :: render() const
{
    if(!m_spImage)
        return;

    
    // TODO: Probably move this queue crap out of system and into a Renderer class
    if(System::get().queued()) {
        std::shared_ptr<const IDepth> spthis = shared_from_this();
        System::get().depthEnqueue(spthis);
    } else {

        if(m_Blend)
            al_set_blender(
                std::get<0>(*m_Blend),
                std::get<1>(*m_Blend),
                std::get<2>(*m_Blend)
            );

        if(m_Tint) {
            // tinted blit
            al_draw_tinted_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), m_Tint->allegro(), pos().x, pos().y, 0);
        }   
        else if(m_bsFlags[F_TILE])
        {
            // fullscreen tile blit
            Vector2 offset(
               fmodf(pos().x, size().x),
               fmodf(pos().y, size().y)
            );
            for(float i = offset.x - size().x;
                i < System::get().w();
                i += size().x)
                for(float j = offset.y - size().y;
                    j < System::get().h();
                    j += size().y)
                {
                    //al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), i, j, 0);
                    image()->render(Vector2(i,j));
                }
            //al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), pos().x, pos().y, 0);
        }
        else
        {
            // normal blit
            if(m_vScale == Vector2(1.0f, 1.0f))
                al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), m_vPos.x, m_vPos.y, 0);
            else
            {
                // scaled blit
                al_draw_scaled_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()),
                    0.0f, 0.0f,
                    al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())),
                    al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())),
                    m_vPos.x, m_vPos.y,
                    al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())) * m_vScale.x,
                    al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())) * m_vScale.y,
                    0);
            }
        }

        if(m_Blend)
            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

    }

}

