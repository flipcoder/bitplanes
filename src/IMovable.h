#ifndef _IMOVABLE_H
#define _IMOVABLE_H

#include <functional>
#include "math/vector2.h"

class IMovable
{
    public:

        IMovable() {}
        virtual ~IMovable() {}
        
        float x() const { return m_vPos.x; }
        float y() const { return m_vPos.y; }
        float dx() const { return m_vVel.x; }
        float dy() const { return m_vVel.y; }

        const Vector2& pos() const { return m_vPos; }
        void pos(float x, float y) {
            m_vPos = Vector2(x,y);
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }
        void pos(const Vector2& pos) {
            m_vPos = pos;
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }
        const Vector2& vel() const { return m_vVel; }
        void vel(Vector2 v) { m_vVel = v; }
        void move(Vector2 rel) {
            m_vPos += rel;
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }

        void callbackOnMove(std::function<void()> cb) {
            m_cbOnMove = cb;
        }

    private:
        
        std::function<void()> m_cbOnMove;
        Vector2 m_vPos;
        Vector2 m_vVel;
};

#endif

