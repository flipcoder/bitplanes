#include "Image.h"
#include "System.h"
#include "Util.h"

Image :: Image(const std::string& fn)
{
    nullify();
    scoped_dtor<Image> dtor(this);
    m_pBitmap = al_load_bitmap(fn.c_str());
    if(!m_pBitmap)
    {
        setError((std::string)"Failed to load bitmap " + fn);
        throw Failure();
    }
    al_convert_mask_to_alpha(m_pBitmap, al_map_rgb(255, 0, 255));
    dtor.resolve();
}

Image :: Image(int w, int h)
{
    nullify();
    scoped_dtor<Image> dtor(this);
    m_pBitmap = al_create_bitmap(w,h);
    if(!m_pBitmap)
    {
        setError("Failed to create bitmap");
        throw Failure();
    }
    dtor.resolve();
}

Image :: ~Image()
{
    al_destroy_bitmap(m_pBitmap);
}


void Image :: render(const Vector2& pos) const
{
    al_draw_bitmap(const_cast<ALLEGRO_BITMAP*>(m_pBitmap), pos.x, pos.y, 0);
}

//void Image :: render(const Vector2& pos, const Vector2& size)
//{
//   al_draw_scaled_bitmap(m_pBitmap,
//       0, 0,
//       al_get_bitmap_width(m_pBitmap),
//       al_get_bitmap_height(m_pBitmap),
//       0, 0,
//       System::get().w(),
//       System::get().h(),
//       0);
//}

