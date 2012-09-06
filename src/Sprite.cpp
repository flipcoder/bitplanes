#include "System.h"
#include "Sprite.h"
#include <cmath>
#include "math/common.h"

Sprite :: Sprite(const std::string& fn)
{
    nullify();
    scoped_dtor<Sprite> dtor(this);
    setImage(System::get().imageResources().cache(fn));
    // below call could be more optimized
    //float rotated_size = Vector2::dist(Vector2(), Vector2(m_spImage->w(),m_spImage->h());
    //m_spRotatedImage.reset(new Image(rotated_size, rotated_size);
    dtor.resolve();
}

void Sprite ::logic(float t) 
{
    Vector2 offset(
       fmodf(x(), w()),
       fmodf(y(), h())
    );
    pos(offset);
}


void Sprite :: render() const
{
    if(!m_spImage)
        return;
    
    // TODO: Probably should move this queue crap out of System and into a Renderer class
    if(System::get().queued()) {
        //std::shared_ptr<const IDepthSortable> spthis = shared_from_this();
        System::get().depthEnqueue(shared_from_this());
    } else {

        if(m_Blend)
            al_set_blender(
                std::get<0>(*m_Blend),
                std::get<1>(*m_Blend),
                std::get<2>(*m_Blend)
            );

        if(m_Tint)
        {
            Vector2 transformed = pos(); //temp
            al_draw_tinted_rotated_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()),
                m_Tint->allegro(),
                //pivot().x, pivot().y,
                //x(), y(),
                0.0f, 0.0f,
                transformed.x, transformed.y,
                rot().degrees(),
                0);
        }
        else if(m_bsFlags[F_TILE])
        {
            IMovable temp;
            // fullscreen tile blit
            Vector2 offset(
               fmodf(x(), size().x),
               fmodf(y(), size().y)
            );
            for(float i = offset.x - size().x;
                i < System::get().w();
                i += size().x)
                for(float j = offset.y - size().y;
                    j < System::get().h();
                    j += size().y)
                {
                    //al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), i, j, 0);
                    temp.pos(i,j);
                    image()->render(&temp);
                }
            //al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()), pos().x, pos().y, 0);
        }
        else
            image()->render(this);

        //else
        //{
        //    // normal blit
        //    if(m_vScale == Vector2(1.0f, 1.0f))
        //        image()->renderAt(pos());
        //    else
        //    {
        //        // scaled blit
        //        al_draw_scaled_bitmap(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap()),
        //            0.0f, 0.0f,
        //            al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())),
        //            al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())),
        //            x(), y(),
        //            al_get_bitmap_width(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())) * m_vScale.x,
        //            al_get_bitmap_height(const_cast<ALLEGRO_BITMAP*>(m_spImage->bitmap())) * m_vScale.y,
        //            0);
        //    }
        //}

        if(m_Blend)
            al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

    }

}

