#include "Sprite.h"

void Sprite :: render()
{
    //masked_blit(m_pBitmap, System::get().buffer(), 0, 0, x(), y(), m_pBitmap->w, m_pBitmap->h);
    al_draw_bitmap(m_pBitmap, x(), y(), 0);
}

