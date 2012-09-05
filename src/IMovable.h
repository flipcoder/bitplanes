#ifndef _IMOVABLE_H
#define _IMOVABLE_H

#include <functional>
#include "math/vector2.h"

// TODO: make callbacks signal/slot
class IMovable:
    public IRealtime
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
            callMove();
        }
        void pos(const Vector2& pos) {
            m_vPos = pos;
            callMove();
        }
        const Vector2& vel() const { return m_vVel; }
        void vel(float x, float y) {
            m_vVel = Vector2(x, y);
            callMove();
        }
        void vel(Vector2 v) { m_vVel = v; }
        void move(Vector2 rel) {
            m_vPos += rel;
            callMove();
        }
        void move(float x, float y) {
            m_vPos += Vector2(x, y);
            callMove();
        }

        void callbackOnMove(std::function<void()> cb) {
            m_cbOnMove = cb;
        }

        void size(Vector2 size) {
            m_vSize = size;
        }
        Vector2 size() const { return m_vSize; }

        Vector2 center() const { return Vector2(m_vPos.x + m_vSize.x/2.0f, m_vPos.y + m_vSize.y/2.0f); }
        void center(Vector2 c) {
            m_vPos = Vector2(c.x - m_vSize.x/2.0f, c.y - m_vSize.y/2.0f);
            callMove();
        }
        void center(float x, float y) {
            center(Vector2(x,y)); // calls move
        }

        void attach(std::shared_ptr<IMovable>& target, Vector2 offset = Vector2()) {
            m_wpTarget = target;
            m_vOffset = offset;
            snapToTarget();
        }

        void dettach() {
            snapToTarget();
            m_wpTarget.reset();
            m_vOffset = Vector2();
        }

        virtual void logic(float t) {
            snapToTarget();
            m_vPos += (m_vVel * t);
            callMove();
        }

        std::shared_ptr<IMovable> target() {
            return m_wpTarget.lock();
        }

        bool attached() const {
            return !m_wpTarget.expired();
        }

    private:

        void snapToTarget() {
            std::shared_ptr<IMovable> target;
            if((target = m_wpTarget.lock()))
                m_vPos = target->pos();
            else
                m_wpTarget.reset();
        }

        void callMove() {
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }
        
        std::function<void()> m_cbOnMove;
        Vector2 m_vPos;
        Vector2 m_vVel;
        Vector2 m_vSize;
        Vector2 m_vOffset;
        std::weak_ptr<IMovable> m_wpTarget;
};

#endif

