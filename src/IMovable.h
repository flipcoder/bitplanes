#ifndef _IMOVABLE_H
#define _IMOVABLE_H

#include <functional>
#include "math/vector2.h"
#include "math/angle.h"
#include "IRealtime.h"

// TODO: make callbacks signal/slot
class IMovable:
    public IRealtime
{
    public:

        IMovable() {}
        virtual ~IMovable() {}

        float x() const {
            snapToTarget();
            return m_vPos.x;
        }
        float y() const {
            snapToTarget();
            return m_vPos.y;
        }
        float dx() const { return m_vVel.x; }
        float dy() const { return m_vVel.y; }
        
        float w() const { return m_vSize.x; }
        float h() const { return m_vSize.y; }

        const Vector2& pos() const {
            snapToTarget();
            return m_vPos;
        }
        void pos(float x, float y) {
            snapToTarget();
            m_vPos = Vector2(x,y);
            callMove();
        }
        void pos(const Vector2& pos) {
            snapToTarget();
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
            snapToTarget();
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
        
        void offset(Vector2 offset) {
            m_vOffset = offset;
        }
        Vector2 offset() const { return m_vOffset; }
        
        void pivot(Vector2 pivot) {
            m_vPivot = pivot;
        }
        Vector2 pivot() const { return m_vPivot; }

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
            m_aRot += m_aOmega;
            callMove();
        }

        std::shared_ptr<IMovable> target() {
            return m_wpTarget.lock();
        }

        bool attached() const {
            return !m_wpTarget.expired();
        }

        // Does not sync targets
        //void sync(const IMovable* newer) {
        //    m_vPos = pos();
        //    m_vVel = vel();
        //    m_vSize = size();
        //    m_vOffset = offset();
        //    //m_wpTarget = target();
        //    m_aRot = rot();
        //}

        Angle rot() const { return m_aRot; }
        void rot(Angle a) { m_aRot=a; }

        bool isRotated() const { return Angle(0.0f) != m_aRot; }

    private:

        void snapToTarget() const {
            std::shared_ptr<IMovable> target;
            if((target = m_wpTarget.lock()))
                m_vPos = target->pos() + m_vOffset;
            else
                m_wpTarget.reset();
        }

        void callMove() {
            try{
                m_cbOnMove();
            }catch(std::bad_function_call&){}
        }
        
        std::function<void()> m_cbOnMove;
        
        // basic stuff
        mutable Vector2 m_vPos; // calculated on the fly based on attachments
        Vector2 m_vVel;
        Vector2 m_vSize;

        // attaching
        Vector2 m_vOffset;
        Vector2 m_vParallax; // linear offset (for shadows, etc.)
        mutable std::weak_ptr<IMovable> m_wpTarget;

        // rotating
        Vector2 m_vPivot;
        Angle m_aRot;
        Angle m_aOmega;
};

#endif

