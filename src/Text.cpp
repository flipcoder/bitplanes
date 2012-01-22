#include "Text.h"
#include "System.h"

void Text :: render() const
{
    if(!m_bVisible)
        return;

    if(System::get().queued()) {
        System::get().depthEnqueue(shared_from_this());
        return;
    }

    al_draw_text(const_cast<Font*>(m_spFont.get())->allegro(), m_Color.allegro(), m_vPos.get().x, m_vPos.get().y,
        m_Align==-1?ALLEGRO_ALIGN_LEFT:
            m_Align==0?ALLEGRO_ALIGN_CENTRE:
            ALLEGRO_ALIGN_RIGHT,
        m_sText.c_str());
}

