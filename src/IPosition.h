#ifndef _IPOSITION_H
#define _IPOSITION_H

// File unused at this point, ignore

#include "math/vector2.h"
#include "Freq.h"

class IPosition
{
    private:
        Freq::Timed<Vector2> m_vPos;

    public:
        IPosition() {}
        virtual ~IPosition() {}
        
        float x() const { return m_vPos.get().x; }
        float y() const { return m_vPos.get().y; }
        Vector2 pos() const { return m_vPos.get(); }
};

#endif

