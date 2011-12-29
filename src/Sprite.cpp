#include "Sprite.h"

void Sprite :: render()
{
    blit(m_pBitmap, System::get().buffer(), x, y, m_pBitmap->w, m_pBitmap->h,
        0, 0, System::get().buffer()->w, System::get().buffer()->h);
}
