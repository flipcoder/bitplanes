#ifndef _IMOVABLE_H
#define _IMOVABLE_H

#include <functional>
#include "math/vector2.h"

class IMovable
{
    public:

        IMovable() {}
        virtual ~IMovable() {}
        
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
            try{
                m_cbOnMove = cb;
            }catch(std::bad_function_call&){}
        }

    private:
        
        std::function<void()> m_cbOnMove;
        Vector2 m_vPos;
        Vector2 m_vVel;
};

#endif

