#include "Image.h"

Image :: Image(const std::string& fn)
{
    m_pBitmap = al_load_bitmap(fn.c_str());
    if(!m_pBitmap)
        setError("Failed to create bitmap");
}

Image :: ~Image()
{
    al_destroy_bitmap(m_pBitmap);
}


void Image :: render(const Vector2& pos)
{
    al_draw_bitmap(m_pBitmap, pos.x, pos.y, 0);
}

void Image :: render(const Vector2& pos, const Vector2& size)
{
    al_draw_scaled_bitmap(m_pBitmap,
        0, 0,
        al_get_bitmap_width(m_pBitmap),
        al_get_bitmap_height(m_pBitmap),
        0, 0,
        System::get().w(),
        System::get().h(),
        0);
}

