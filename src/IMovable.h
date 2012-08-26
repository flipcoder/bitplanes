#ifndef _IMOVABLE_H
#define _IMOVABLE_H

#include <functional>
#include "math/vector2.h"

// make callbacks signal/slot
class IMovable
{
    public:

        IMovable() {}
        virtual ~IMovable() {}

        float x() const { return m_vPos.x; }
        float y() const { return m_vPos.y; }
        float dx() const { return m_vVel.x; }
        float dy() const { return m_vVel.y; }
        
        float w() const { return m_vSize.x; }
        float h() const { return m_vSize.y; }

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
        void vel(float x, float y) {
            m_vVel = Vector2(x, y);
        }
        void vel(Vector2 v) { m_vVel = v; }
        void move(Vector2 rel) {
            m_vPos += rel;
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }
        void move(float x, float y) {
            m_vPos += Vector2(x, y);
        }

        void callbackOnMove(std::function<void()> cb) {
            m_cbOnMove = cb;
        }

        void size(Vector2 size) {
            m_vSize = size;
        }
        Vector2 size() const { return m_vSize; }
        Vector2 origin() const { return Vector2(m_vPos.x + m_vSize.x/2.0f, m_vPos.y + m_vSize.y/2.0f); }

    private:
        
        std::function<void()> m_cbOnMove;
        Vector2 m_vPos;
        Vector2 m_vVel;
        Vector2 m_vSize;
};

#endif

